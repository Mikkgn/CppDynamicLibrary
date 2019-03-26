from ctypes import *
from typing import Union, Type


def load_dll() -> CDLL:
    return cdll.LoadLibrary("Debug/CppDynamicLibrary.dll")


def get_function_from_dll(dll_handle: CDLL, func_name: str,
                          returned_type: Union[Type[c_char_p], Type[c_char], None]) -> CFUNCTYPE:
    func = getattr(dll_handle, func_name)
    func.restype = returned_type
    return func


def print_info(name: str, group_name: str):
    print(f"Student name: {name} \n Student group: {group_name}")


def main():
    dll_handle = load_dll()
    get_name_func = get_function_from_dll(dll_handle, 'GetName', c_char_p)
    get_group_name_func = get_function_from_dll(dll_handle, 'GetGroupName', c_char_p)
    student_name: str = get_name_func().decode(errors='ignore')
    group_name: str = get_group_name_func().decode(errors='ignore')
    print_info(student_name, group_name)


if __name__ == '__main__':
    main()
