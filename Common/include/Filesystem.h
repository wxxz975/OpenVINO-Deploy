#pragma once


#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;
typedef std::string Path;

namespace Common
{

    namespace IFilesystem
    {
        /// @brief 获取当前可执行文件的路径
        /// @return 返回这个路径
        Path GetCurrentPath();

        /// @brief 创建一个文件夹
        /// @param path 需要创建的文件路径
        /// @return 返回是否创建成功
        bool CreateDir(const Path& path);

        /// @brief 首先获取当前的可执行文件路径，并且把这个传入的相对路径reletive_path拼接到可执行路径后面
        /// @param relative_path 相对路径
        /// @return 返回拼接好的路径
        Path JoinCurrentPath(const Path& relative_path);

        /// @brief 拼接两个路径，解决重复出现 / \\的问题
        /// @param left 左边的路径
        /// @param right 右边的路径
        /// @return 返回拼接好的路径
        Path ConcatPath(const Path& left, const Path& right);


        /// @brief 获取一个路径中的文件名
        /// @param path 完整路径
        /// @return 返回文件名
        std::string GetFilename(const Path& path);

        /// @brief 获取一个完整文件路径中的后缀
        /// @param path 路径
        /// @return 返回后缀
        std::string GetExtension(const Path& path);

        /// @brief 获取父级目录
        /// @param path 完整的路径
        /// @return 返回父级目录
        Path GetParentPath(const Path& path);


        /// @brief 根据文件的后缀匹配
        /// @param path 查询的路径
        /// @param ext 后缀, 不带点, 比如后缀 onnx, jpg
        /// @return 返回获取到的路径集合
        std::vector<std::string> GetFilesBySuffix(const Path& path, const std::string& ext);


        /// @brief 根据所给的路径获取符合正则表示的路径
        /// @param path 需要查询的路径
        /// @param reg 正则表达式
        /// @return 返回获取到的路径集合
        std::vector<std::string> GetFilesByRegex(const Path& path, const std::string reg);

        /// @brief 判断某个文件或者路径是否存在
        /// @param path 路径
        /// @return true 存在
        bool IsExist(const Path& path);

        /// @brief 判断是否是文件夹
        /// @param path 
        /// @return 
        bool IsDir(const Path& path);

        /// @brief 判断是否是文件
        /// @param path 
        /// @return 
        bool IsFile(const Path& path);

        /// @brief 判断这个string是否是以ending结尾
        /// @param string 
        /// @param end 
        /// @return 
        bool IsEndWith(const std::string& string, const std::string& ending);


        /// @brief 判断这个string是否是以prefix开始
        /// @param string 
        /// @param prefix 
        /// @return 
        bool IsStartWith(const std::string& string, const std::string& prefix);


        /// <summary>
        /// 使用正则表达式在string中匹配正则pattern查看是否匹配成功
        /// </summary>
        /// <param name="string">原始字符串</param>
        /// <param name="pattern">模式</param>
        /// <returns></returns>
        bool RegexMatch(const std::string& string, const std::string& pattern);
    }; // IFilesystem



};// Common