import os
import xmltodict
import torch
import torchvision.transforms as transform
from PIL import Image
from torch.distributions import transform_to
from torch.utils.data import Dataset


class VOCDataset(Dataset):
    def __init__(self, image_folder, label_folder, transform, lable_tranform):
        self.image_folder = image_folder
        self.label_folder = label_folder
        self.transform = transform
        self.label_transform = lable_tranform
        self.image_names = os.listdir(self.image_folder)
        self.class_list = ["no helmet", "motor", "number", "with helmet"]

    def __len__(self):
        return len(self.image_names)

    def __getitem__(self, index):
        image_name = self.image_names[index]
        image_path = os.path.join(self.image_folder, image_name)
        image = Image.open(image_path).convert("RGB")

        label_name = image_name.split(".")[0] + ".xml"
        label_path = os.path.join(self.label_folder, label_name)
        with open(label_path, "r", encoding="utf-8") as f:
            label_content = f.read()
        label_dict = xmltodict.parse(label_content)
        objects = label_dict["annotation"]["object"]
        target = []
        for object in objects:
            object_name = object["name"]
            object_class_id = self.class_list.index(object_name)
            object_xmax = float(object["bndbox"]["xmax"])
            object_ymax = float(object["bndbox"]["ymax"])
            object_xmin = float(object["bndbox"]["xmin"])
            object_ymin = float(object["bndbox"]["ymin"])
            label_content = (
                f"{object_name} {object_xmax} {object_xmin} {object_ymax} {object_ymin}"
            )
            target.extend(
                [object_class_id, object_xmax, object_xmin, object_ymax, object_ymin]
            )
        target = torch.tensor(target)
        # 对图片进行处理，转化为tensor
        if self.transform:
            image = self.transform(image)
        return image, target


if __name__ == "__main__":
    train_dataset = VOCDataset(
        r"/home/lnick/GitHub/Program/Python/Python项目/CV/YOLO/DataSet/VOC/HelmetDataset-VOC/train/images",
        r"/home/lnick/GitHub/Program/Python/Python项目/CV/YOLO/DataSet/VOC/HelmetDataset-VOC/train/labels",
        transform=transform.Compose([transform.ToTensor()]),
        lable_tranform=None,
    )
    print(len(train_dataset))
    print(train_dataset[11])
