# CppTemplate
这是一个基于CMake的简单模板, 用于想法的验证

# Git Remote更换脚本使用指南

本项目提供了三个跨平台的脚本来帮助你轻松更换Git仓库的remote地址。

## 📁 脚本文件

- **`change-remote.sh`** - Shell脚本（Linux/macOS）
- **`change-remote.bat`** - Windows批处理脚本  
- **`change-remote.py`** - Python脚本（真正跨平台）

## 🚀 快速开始

### Linux/macOS 使用Shell脚本

```bash
# 基本用法
./change-remote.sh MyProject

# 指定自定义GitHub路径
./change-remote.sh MyProject https://github.com/username/

# 查看帮助
./change-remote.sh --help
```

### Windows 使用批处理脚本

```cmd
rem 基本用法
change-remote.bat MyProject

rem 指定自定义GitHub路径  
change-remote.bat MyProject https://github.com/username/

rem 查看帮助
change-remote.bat --help
```

### 跨平台 使用Python脚本

```bash
# 基本用法
python3 change-remote.py MyProject

# 指定自定义GitHub路径
python3 change-remote.py MyProject https://github.com/username/

# 干运行模式（只显示操作，不实际执行）
python3 change-remote.py --dry-run MyProject

# 执行完成后测试连接
python3 change-remote.py --test MyProject

# 查看帮助
python3 change-remote.py --help
```

## 参数说明

### 必需参数
- **`<仓库名>`**: 要更换的仓库名称（例如：MyProject）

### 可选参数
- **`[GitHub路径]`**: GitHub用户路径，默认为 `https://github.com/lzorn-lzorn/`

### Python脚本特殊选项
- **`--dry-run`**: 只显示将要执行的操作，不实际执行
- **`--test`**: 执行完成后测试与远程仓库的连接
- **`-h, --help`**: 显示帮助信息

## 脚本功能
- 自动检查当前目录是否为Git仓库
- 验证远程仓库是否存在
- 如果仓库不存在，脚本不会执行任何操作

## 使用示例

### 场景1：更换到你的默认GitHub账户下的仓库

```bash
# 当前仓库URL会变更为：https://github.com/lzorn-lzorn/NewProject.git
./change-remote.sh NewProject
```

### 场景2：更换到其他用户的仓库

```bash  
# 当前仓库URL会变更为：https://github.com/otheruser/MyProject.git
./change-remote.sh MyProject https://github.com/otheruser/
```

### 场景3：测试模式（仅Python脚本）

```bash
# 先查看会执行什么操作
python3 change-remote.py --dry-run MyProject

# 确认无误后正式执行并测试连接
python3 change-remote.py --test MyProject
```

## 注意事项

1. **仓库存在性检查**: 脚本会先检查远程仓库是否存在，只有存在时才会执行操作
2. **权限要求**: 确保脚本有执行权限（Linux/macOS需要 `chmod +x`）
3. **网络连接**: 需要良好的网络连接来验证远程仓库
4. **Git环境**: 确保系统已安装Git并可在命令行使用

## 输出示例

```
=== Git Remote仓库更换脚本 ===
[INFO] 仓库名: MyProject
[INFO] GitHub路径: https://github.com/lzorn-lzorn/
[INFO] 完整URL: https://github.com/lzorn-lzorn/MyProject.git
[INFO] 检查远程仓库是否存在...
[SUCCESS] 远程仓库存在，继续执行...
[INFO] 当前remote配置:
  origin  https://github.com/olduser/oldrepo.git (fetch)
  origin  https://github.com/olduser/oldrepo.git (push)
[INFO] 更新existing origin remote...
[SUCCESS] 成功更新origin remote URL
[INFO] 更新后的remote配置:
  origin  https://github.com/lzorn-lzorn/MyProject.git (fetch)
  origin  https://github.com/lzorn-lzorn/MyProject.git (push)
[SUCCESS] Remote仓库更换完成！
```


## 常见问题

**Q: 提示"当前目录不是Git仓库"**
A: 确保在Git仓库目录中执行脚本

**Q: 提示"远程仓库不存在"**  
A: 检查仓库名称和GitHub路径是否正确，确保仓库确实存在

**Q: Windows上颜色显示不正常**
A: 使用Python脚本，它会自动处理Windows的颜色支持

**Q: 权限被拒绝**
A: 在Linux/macOS上使用 `chmod +x script-name` 给予执行权限

