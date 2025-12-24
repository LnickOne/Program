#include "HttpServer.h"
#include "HttpContext.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Logger.h"
#include <time.h>
#include <any>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cctype>
#include <algorithm>

using namespace std;

/**
 * HttpServer构造函数
 */
HttpServer::HttpServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameArg)
    : server_(loop, listenAddr, nameArg)
{
    // 设置TcpServer的回调函数
    server_.setConnectionCallback(
        bind(&HttpServer::onConnection, this, placeholders::_1));
    server_.setMessageCallback(
        bind(&HttpServer::onMessage, this, placeholders::_1, placeholders::_2));
}

/**
 * HttpServer析构函数
 */
HttpServer::~HttpServer()
{
}

/**
 * 设置线程数量
 */
// void HttpServer::setThreadNum(int numThreads) {
//     server_.setThreadNum(numThreads);
// }

/**
 * 启动服务器
 */
void HttpServer::start()
{
    LOG_INFO << "HttpServer start listening on " << server_.name();
    server_.start();
}

/**
 * 连接建立回调函数
 */
void HttpServer::onConnection(const shared_ptr<TcpConnection> &conn)
{
    if (conn->connected())
    {
        LOG_INFO << "HttpServer::onConnection(): new connection [" << conn->name()
                 << "] from " << conn->peerAddress().toIpPort();
        // 为新连接创建HTTP上下文
        conn->setContext(std::any(HttpContext()));
    }
    else
    {
        LOG_INFO << "HttpServer::onConnection(): connection [" << conn->name()
                 << "] is down";
    }
}

/**
 * 消息到达回调函数
 */
void HttpServer::onMessage(const shared_ptr<TcpConnection> &conn, string &buf)
{
    HttpContext *context = std::any_cast<HttpContext>(conn->getMutableContext());

    // 解析HTTP请求
    if (!context->parseRequest(&buf[0], buf.size(), time(NULL)))
    {
        // 解析失败，发送400错误响应
        HttpResponse response(true);
        response.setStatusCode(HttpResponse::k400BadRequest);
        response.setStatusMessage("Bad Request");
        response.setCloseConnection(true);
        response.setBody("<html><head><title>400 Bad Request</title></head><body><h1>400 Bad Request</h1><p>The request could not be understood by the server due to malformed syntax.</p></body></html>");
        string output;
        response.appendToBuffer(output);
        conn->send(output);
        conn->shutdown();
    }

    // 检查是否解析完成
    if (context->gotAll())
    {
        // 处理HTTP请求
        onRequest(conn, context->request());
        // 重置HTTP上下文，准备处理下一个请求
        context->reset();
    }
}

/**
 * 生成错误响应页面
 */
string generateErrorPage(HttpResponse::HttpStatusCode statusCode, const string &statusMessage, const string &requestPath)
{
    string body;
    body += "<html><head><title>"; // 确保字符串正确构建
    body += to_string(statusCode) + " " + statusMessage;
    body += "</title>";
    body += "<style>body { font-family: Arial, sans-serif; margin: 40px; }"
            "h1 { color: #333; }"
            ".error { color: #d9534f; }"
            ".info { margin-top: 30px; color: #666; }</style></head>";
    body += "<body><div class='error'><h1>" + to_string(statusCode) + " " + statusMessage + "</h1></div>";
    body += "<div class='info'><p>Requested URL: " + requestPath + "</p></div>";
    body += "<div class='info'><p>Powered by MyHttpServer</p></div>";
    body += "</body></html>";
    return body;
}

/**
 * 根据文件扩展名获取Content-Type
 */
string HttpServer::getContentTypeByExtension(const string &path)
{
    string contentType = "text/plain";
    size_t dotPos = path.rfind('.');
    if (dotPos != string::npos)
    {
        string ext = path.substr(dotPos + 1);
        transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

        // 文本类型
        if (ext == "html" || ext == "htm")
            contentType = "text/html";
        else if (ext == "css")
            contentType = "text/css";
        else if (ext == "js")
            contentType = "text/javascript";
        else if (ext == "txt")
            contentType = "text/plain";
        else if (ext == "json")
            contentType = "application/json";
        else if (ext == "xml")
            contentType = "application/xml";
        
        // 图片类型
        else if (ext == "jpg" || ext == "jpeg")
            contentType = "image/jpeg";
        else if (ext == "png")
            contentType = "image/png";
        else if (ext == "gif")
            contentType = "image/gif";
        else if (ext == "ico")
            contentType = "image/x-icon";
        else if (ext == "svg")
            contentType = "image/svg+xml";
        
        // 应用类型
        else if (ext == "pdf")
            contentType = "application/pdf";
        else if (ext == "zip")
            contentType = "application/zip";
        else if (ext == "rar")
            contentType = "application/x-rar-compressed";
        else if (ext == "tar")
            contentType = "application/x-tar";
        else if (ext == "gz")
            contentType = "application/gzip";
        
        // 音频类型
        else if (ext == "mp3")
            contentType = "audio/mpeg";
        else if (ext == "wav")
            contentType = "audio/wav";
        else if (ext == "ogg")
            contentType = "audio/ogg";
        
        // 视频类型
        else if (ext == "mp4")
            contentType = "video/mp4";
        else if (ext == "webm")
            contentType = "video/webm";
        else if (ext == "ogv")
            contentType = "video/ogg";
        
        // 字体类型
        else if (ext == "ttf")
            contentType = "font/ttf";
        else if (ext == "woff")
            contentType = "font/woff";
        else if (ext == "woff2")
            contentType = "font/woff2";
        else if (ext == "eot")
            contentType = "application/vnd.ms-fontobject";
    }
    return contentType;
}

/**
 * 处理静态文件请求
 */
bool HttpServer::handleStaticFile(const HttpRequest &req, HttpResponse *resp)
{
    // 只处理GET请求
    if (req.method() != HttpRequest::kGet)
    {
        resp->setStatusCode(HttpResponse::k405MethodNotAllowed);
        resp->setContentType("text/html");
        resp->setBody(generateErrorPage(resp->k405MethodNotAllowed, "Method Not Allowed", req.path()));
        resp->addHeader("Allow", "GET");
        return true; // 返回true表示已经处理了请求（返回了错误响应）
    }

    // 获取请求路径
    string path = req.path();

    // 如果路径以/结尾，默认添加index.html
    if (path.empty() || path[path.size() - 1] == '/')
    {
        path += "index.html";
    }

    // 尝试从缓存中获取
    shared_ptr<CacheEntry> cacheEntry = cacheManager_.getCache(path);
    if (cacheEntry)
    {
        // 缓存命中，直接使用缓存内容
        resp->setStatusCode(HttpResponse::k200Ok);
        resp->setContentType(cacheEntry->getContentType());
        resp->setBody(cacheEntry->getContent());
        resp->addHeader("Content-Length", to_string(cacheEntry->getContent().size()));
        resp->addHeader("X-Cache", "HIT");
        return true;
    }

    // 构建完整的文件路径
    string fullPath = staticFileRoot_ + path;

    // 防止路径遍历攻击 - 使用规范化路径确保安全
    try
    {
        // 获取规范化路径
        filesystem::path canonicalPath = filesystem::canonical(fullPath);
        filesystem::path canonicalRoot = filesystem::canonical(staticFileRoot_);

        // 检查规范化后的路径是否仍然在静态文件根目录内
        if (!filesystem::equivalent(canonicalPath.parent_path(), canonicalRoot) &&
            canonicalPath.string().find(canonicalRoot.string() + "/") != 0)
        {
            resp->setStatusCode(HttpResponse::k403Forbidden);
            resp->setContentType("text/html");
            resp->setBody(generateErrorPage(resp->k403Forbidden, "Forbidden", req.path()));
            return true;
        }

        // 更新fullPath为规范化路径
        fullPath = canonicalPath.string();
    }
    catch (const filesystem::filesystem_error &e)
    {
        // 如果规范化失败（例如文件不存在），不影响后续处理
    }

    // 检查文件是否存在
    if (!filesystem::exists(fullPath))
    {
        return false; // 返回false让调用者处理404
    }

    // 检查是否是常规文件
    if (!filesystem::is_regular_file(fullPath))
    {
        resp->setStatusCode(HttpResponse::k403Forbidden);
        resp->setContentType("text/html");
        resp->setBody(generateErrorPage(resp->k403Forbidden, "Forbidden", req.path()));
        return true;
    }

    // 检查文件是否可读
    ifstream file(fullPath, ios::binary);
    if (!file.is_open())
    {
        resp->setStatusCode(HttpResponse::k403Forbidden);
        resp->setContentType("text/html");
        resp->setBody(generateErrorPage(resp->k403Forbidden, "Forbidden", req.path()));
        return true;
    }

    // 读取文件内容
    stringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();
    file.close();

    // 根据文件扩展名设置Content-Type
    string contentType = getContentTypeByExtension(path);

    // 设置响应
    resp->setStatusCode(HttpResponse::k200Ok);
    resp->setContentType(contentType);
    resp->setBody(fileContent);
    resp->addHeader("Content-Length", to_string(fileContent.size()));
    resp->addHeader("X-Cache", "MISS");

    // 将文件内容添加到缓存（缓存1小时）
    cacheManager_.addCache(path, fileContent, contentType, 3600);

    return true;
}

/**
 * 处理HTTP请求
 */
void HttpServer::onRequest(const shared_ptr<TcpConnection> &conn, const HttpRequest &req)
{
    const string &connection = req.getHeader("Connection");
    bool close = connection == "close" ||
                 (req.version() == HttpRequest::kHttp10 && connection != "Keep-Alive");
    HttpResponse response(close);

    // 首先尝试处理静态文件请求
    if (!staticFileRoot_.empty())
    {
        // 构建完整的文件路径
        string path = req.path();
        if (path.empty() || path[path.size() - 1] == '/')
        {
            path += "index.html";
        }
        string fullPath = staticFileRoot_ + path;

        // 检查文件是否存在
        if (filesystem::exists(fullPath))
        {
            // 文件存在，尝试处理静态文件请求
            if (!handleStaticFile(req, &response) && httpCallback_)
            {
                // 静态文件处理失败（比如权限问题），调用回调函数
                httpCallback_(req, &response);

                // 如果回调函数没有设置状态码，默认使用200 OK
                if (response.getStatusCode() == HttpResponse::kUnknown)
                {
                    response.setStatusCode(HttpResponse::k200Ok);
                }
            }
        }
        else
        {
            // 文件不存在，返回404错误
            response.setStatusCode(HttpResponse::k404NotFound);
            response.setContentType("text/html");
            response.setBody(generateErrorPage(response.k404NotFound, "Not Found", req.path()));
        }
    }
    // 如果没有设置静态文件根目录，调用用户提供的HTTP请求处理回调函数
    else if (httpCallback_)
    {
        httpCallback_(req, &response);

        // 如果回调函数没有设置状态码，默认使用200 OK
        if (response.getStatusCode() == HttpResponse::kUnknown)
        {
            response.setStatusCode(HttpResponse::k200Ok);
        }
    }
    else
    {
        // 如果没有设置回调函数，返回404错误
        response.setStatusCode(HttpResponse::k404NotFound);
        response.setContentType("text/html");
        response.setBody(generateErrorPage(response.k404NotFound, "Not Found", req.path()));
    }

    // 发送HTTP响应
    string output;
    response.appendToBuffer(output);
    conn->send(output);

    // 如果需要关闭连接
    if (response.closeConnection())
    {
        conn->shutdown();
    }
}