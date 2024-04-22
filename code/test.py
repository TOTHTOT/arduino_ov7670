import os

def hex_string_to_c_array(hex_string):
    # 去除空格并拆分十六进制字符串
    hex_string = hex_string.replace(' ', '')
    hex_list = [hex_string[i:i+2] for i in range(0, len(hex_string), 2)]

    # 将十六进制转换为C语言格式的数组字符串，每16个数据自动换行
    c_array = ""
    for i, hex_value in enumerate(hex_list):
        c_array += "0x" + hex_value.upper() + ", "
        if (i + 1) % 16 == 0:  # 每16个数据添加换行符
            c_array += "\n    "

    # 去除末尾多余的逗号和空格
    c_array = c_array.rstrip(", ")

    # 将数据格式化为C数组格式
    c_array = "{" + c_array + "};"
    return c_array

def save_bytes_to_txt(byte_array, filename):
    with open(filename, 'w') as f:
        for byte in byte_array:
            f.write(str(byte) + '\n')

if __name__ == "__main__":
    # 获取当前文件所在目录的绝对路径
    current_dir = os.path.dirname(os.path.abspath(__file__))
    
    # 构造input_arry.txt文件的绝对路径
    input_file_path = os.path.join(current_dir, "input_arry.txt")
    output_file_path = os.path.join(current_dir, "output_arry.txt")

    # 打开input_arry.txt文件并读取内容
    with open(input_file_path, "r") as f:
        hex_string = f.read()
        c_array_string = hex_string_to_c_array(hex_string)

    # 将转换后的结果写入output_arry.txt文件中
    with open(output_file_path, "w") as output_file:
        output_file.write("uint8_t image_data[] = " + c_array_string)
