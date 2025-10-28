@echo off
setlocal EnableDelayedExpansion

REM 跨平台Git Remote仓库更换脚本 (Windows批处理版本)
REM 用法: change-remote.bat <仓库名> [GitHub路径]
REM 
REM 参数:
REM   仓库名: 必需，要更换的仓库名称
REM   GitHub路径: 可选，默认为 https://github.com/lzorn-lzorn/
REM
REM 示例:
REM   change-remote.bat MyProject
REM   change-remote.bat MyProject https://github.com/username/
REM

REM 默认GitHub路径
set DEFAULT_GITHUB_PATH=https://github.com/lzorn-lzorn/

REM 显示使用帮助
if "%1"=="-h" goto :show_help
if "%1"=="--help" goto :show_help
if "%1"=="/?" goto :show_help

REM 检查参数
if "%1"=="" (
    echo [ERROR] 缺少必需参数
    echo.
    goto :show_help
)

REM 获取参数
set REPO_NAME=%1
if "%2"=="" (
    set GITHUB_PATH=%DEFAULT_GITHUB_PATH%
) else (
    set GITHUB_PATH=%2
)

REM 确保GitHub路径以/结尾
set LAST_CHAR=!GITHUB_PATH:~-1!
if not "!LAST_CHAR!"=="/" (
    set GITHUB_PATH=!GITHUB_PATH!/
)

REM 构建完整的仓库URL
set REPO_URL=!GITHUB_PATH!!REPO_NAME!.git

echo [INFO] 开始更换remote仓库...
echo [INFO] 仓库名: %REPO_NAME%
echo [INFO] GitHub路径: !GITHUB_PATH!
echo [INFO] 完整URL: !REPO_URL!

REM 检查是否在git仓库中
git rev-parse --git-dir >nul 2>&1
if errorlevel 1 (
    echo [ERROR] 当前目录不是Git仓库
    exit /b 1
)

REM 检查远程仓库是否存在
echo [INFO] 检查远程仓库是否存在...

REM 使用git ls-remote检查仓库是否存在
git ls-remote "!REPO_URL!" >nul 2>&1
if errorlevel 1 (
    echo [WARNING] 远程仓库 '!REPO_URL!' 不存在或无法访问
    echo [INFO] 跳过操作，不进行任何更改
    exit /b 0
)

echo [SUCCESS] 远程仓库存在，继续执行...

REM 显示当前的remote配置
echo [INFO] 当前remote配置:
git remote -v

REM 检查origin是否已存在
git remote get-url origin >nul 2>&1
if errorlevel 1 (
    echo [INFO] 添加新的origin remote...
    git remote add origin "!REPO_URL!"
    if errorlevel 1 (
        echo [ERROR] 添加origin remote失败
        exit /b 1
    )
    echo [SUCCESS] 成功添加origin remote
) else (
    echo [INFO] 更新existing origin remote...
    git remote set-url origin "!REPO_URL!"
    if errorlevel 1 (
        echo [ERROR] 更新origin remote URL失败
        exit /b 1
    )
    echo [SUCCESS] 成功更新origin remote URL
)

REM 显示更新后的remote配置
echo.
echo [INFO] 更新后的remote配置:
git remote -v

REM 可选：测试连接
echo.
set /p TEST_CONNECTION="是否测试与新remote的连接? (y/N): "
if /i "!TEST_CONNECTION!"=="y" (
    echo [INFO] 测试连接到 !REPO_URL! ...
    git ls-remote origin >nul 2>&1
    if errorlevel 1 (
        echo [WARNING] 连接测试失败，请检查URL和网络连接
    ) else (
        echo [SUCCESS] 连接测试成功！
    )
)

echo [SUCCESS] Remote仓库更换完成！
goto :eof

:show_help
echo Git Remote仓库更换脚本 (Windows版)
echo.
echo 用法: %~nx0 ^<仓库名^> [GitHub路径]
echo.
echo 参数:
echo   仓库名      必需，要更换的仓库名称
echo   GitHub路径  可选，默认为 %DEFAULT_GITHUB_PATH%
echo.
echo 示例:
echo   %~nx0 MyProject
echo   %~nx0 MyProject https://github.com/username/
echo.
echo 选项:
echo   -h, --help, /?  显示此帮助信息
echo.
exit /b 0