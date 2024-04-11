#include "Filesystem.h"

#include <regex>

namespace Common
{
    namespace IFilesystem
    {
        Path GetCurrentPath()
        {
            return fs::current_path().string();
        }

        bool CreateDir(const Path& path)
        {
            return fs::create_directory(path);;
        }

        Path JoinCurrentPath(const Path& relative_path)
        {
            Path curPath = GetCurrentPath();
            return ConcatPath(curPath, relative_path);
        }

        Path ConcatPath(const Path& left, const Path& right)
        {
            fs::path lpath(left);
            fs::path rpath(right);

            return (lpath / rpath).string();
        }

        std::string GetFilename(const Path& path)
        {
            return fs::path(path).filename().string();
        }

        std::string GetExtension(const Path& path)
        {
            return fs::path(path).extension().string();
        }

        Path GetParentPath(const Path& path)
        {
            return fs::path(path).parent_path().string();
        }


        ///比如匹配jpg后缀的文件 "\\.jpg$"
        std::vector<std::string> GetFilesBySuffix(const Path& path, const std::string& extPat)
        {
            std::vector<std::string> result;
            if (IsExist(path)) {
                for (const auto& entry : std::filesystem::directory_iterator(path))
                {
                    if (!entry.is_regular_file())
                        continue;

                    std::string extension = entry.path().extension().string();
                    if (extension.size() < 1)
                        continue;

                    extension = extension.substr(1);

                    if (extension != extPat)
                        continue;

                    result.push_back(entry.path().string());
                }
            }

            return result;
        }

        std::vector<std::string> GetFilesByRegex(const Path& path, const std::string reg)
        {
            std::vector<std::string> result;
            std::regex regex(reg);
            if (IsExist(path)) {
                for (const auto& entry : std::filesystem::directory_iterator(path))
                {
                    if (!entry.is_regular_file())
                        continue;

                    std::string filename = entry.path().filename().string();
                    if (!RegexMatch(filename, reg))
                        continue;

                    result.push_back(entry.path().string());
                }
            }

            return result;
        }

        bool IsExist(const Path& path)
        {
            return fs::exists(path);
        }


        bool IsDir(const Path& path)
        {
            return fs::is_directory(path);
        }

        bool IsFile(const Path& path)
        {
            return !IsDir(path);
        }

        bool IsEndWith(const std::string& string, const std::string& ending)
        {
            if (string.length() < ending.length()) {
                return false;
            }
            return string.substr(string.length() - ending.length()) == ending;
        }

        bool IsStartWith(const std::string& string, const std::string& prefix)
        {
            if (prefix.length() > string.length())
                return false;

            return string.compare(0, prefix.length(), prefix) == 0;
        }

        bool RegexMatch(const std::string& string, const std::string& pattern)
        {
            std::regex pat(pattern);
            return std::regex_match(string, pat);
        }

    };


};