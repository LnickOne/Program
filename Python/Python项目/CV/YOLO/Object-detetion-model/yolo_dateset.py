import os
import xmltodict
import torch
import torchvision.transforms as transform
from PIL import Image
from torch.distributions import transform_to
from torch.utils.data import Dataset


class YOLODataset(Dataset):
    def __init__(self, image_folder, label_folder, transform, lable_tranform):
        self.image_folder = image_folder
        self.label_folder = label_folder
        self.transform = transform
        self.label_transform = lable_tranform
        self.image_names = os.listdir(self.image_folder)
        # self.class_list = ["no helmet", "motor", "number", "with helmet"] 不需要了，因为yolo的格式已经是数字了

    def __len__(self):
        return len(self.image_names)

    def __getitem__(self, index):
        image_name = self.image_names[index]
        image_path = os.path.join(self.image_folder, image_name)
        image = Image.open(image_path).convert("RGB")

        label_name = image_name.split(".")[0] + ".txt"  # yolo的后缀是txt
        label_path = os.path.join(self.label_folder, label_name)
        with open(label_path, "r", encoding="utf-8") as f:
            label_content = f.read()
        object_infos = label_content.strip().split("\n")
        target = []
        for object_info in object_infos:
            info_list = object_info.strip().split(" ")
            class_id = float(info_list[0])
            center_x = float(info_list[1])
            center_y = float(info_list[2])
            width = float(info_list[3])
            height = float(info_list[4])
            target.extend([class_id, center_x, center_y, width, height])

        # label_dict = xmltodict.parse(label_content)
        # objects = label_dict["annotation"]["object"]
        # target = []
        # for object in objects:
        #     object_name = object["name"]
        #     object_class_id = self.class_list.index(object_name)
        #     object_xmax = float(object["bndbox"]["xmax"])
        #     object_ymax = float(object["bndbox"]["ymax"])
        #     object_xmin = float(object["bndbox"]["xmin"])
        #     object_ymin = float(object["bndbox"]["ymin"])
        #     label_content = (
        #         f"{object_name} {object_xmax} {object_xmin} {object_ymax} {object_ymin}"
        #     )
        #     target.extend(
        #         [object_class_id, object_xmax, object_xmin, object_ymax, object_ymin]
        #     )
        target = torch.tensor(target)
        # 对图片进行处理，转化为tensor
        if self.transform:
            image = self.transform(image)
        return image, target


if __name__ == "__main__":
    train_dataset = YOLODataset(
        r"/home/lnick/GitHub/Program/Python/Python项目/CV/YOLO/DataSet/YOLO/HelmetDataset-YOLO-Train/images",
        r"/home/lnick/GitHub/Program/Python/Python项目/CV/YOLO/DataSet/YOLO/HelmetDataset-YOLO-Train/labels",
        transform=transform.Compose([transform.ToTensor()]),
        lable_tranform=None,
    )
    print(len(train_dataset))
    print(train_dataset[11])
