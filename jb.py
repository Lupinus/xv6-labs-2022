import os
import shutil


def copy_files(source_dir, dest_dir):
    # 获取源目录和目标目录中的所有文件
    source_files = os.listdir(source_dir)
    dest_files = os.listdir(dest_dir)

    # 找到两个目录中同名的文件
    common_files = set(source_files) & set(dest_files)

    for file_name in common_files:
        source_path = os.path.join(source_dir, file_name)
        dest_path = os.path.join(dest_dir, file_name)

        # 判断文件是否为普通文件
        if os.path.isfile(source_path) and os.path.isfile(dest_path):
            # 复制源文件的内容到目标文件
            shutil.copy(source_path, dest_path)
            print(f"复制文件 {file_name} 的内容成功")


# 设置源目录和目标目录
source_directory = "/home/yt/pre"
dest_directory = "/home/yt/xv6-labs-2022"

# 调用复制函数
copy_files(source_directory, dest_directory)
