use rand::{thread_rng, Rng};
use std::{cmp::Ordering, io};

fn main() {
    println!("猜数字游戏!");
    let secret_number = thread_rng().gen_range(1, 101);
    println!("神秘数字是: {}", secret_number);

    loop {
        println!("请输入你的猜测:");
        let mut guess = String::new();
        io::stdin().read_line(&mut guess).expect("无法读取用户输入");
        //shadow
        let guess: u32= match guess.trim().parse() {
            Ok(num) => num,
            Err(_) => {
                println!("无法读取，请输入一个数字!");
                continue;
            }
        };
        println!("你猜的数字是: {}", guess);
        match guess.cmp(&secret_number) {
            Ordering::Less => println!("太小了!"),
            Ordering::Greater => println!("太大了!"),
            Ordering::Equal => {
                println!("恭喜你猜对了!");
                break;
            }
        }
    }
}
