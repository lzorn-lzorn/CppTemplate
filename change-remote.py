#!/usr/bin/env python3
"""
跨平台Git Remote仓库更换脚本 (Python版本)

用法: python change-remote.py <仓库名> [GitHub路径]

参数:
  仓库名: 必需，要更换的仓库名称  
  GitHub路径: 可选，默认为 https://github.com/lzorn-lzorn/

示例:
  python change-remote.py MyProject
  python change-remote.py MyProject https://github.com/username/
"""

import sys
import subprocess
import argparse
import os
from urllib.parse import urljoin

# ANSI颜色代码（在Windows上需要启用ANSI支持）
class Colors:
    RED = '\033[0;31m'
    GREEN = '\033[0;32m'
    YELLOW = '\033[1;33m'
    BLUE = '\033[0;34m'
    PURPLE = '\033[0;35m'
    CYAN = '\033[0;36m'
    WHITE = '\033[1;37m'
    NC = '\033[0m'  # No Color

# 默认配置
DEFAULT_GITHUB_PATH = "https://github.com/lzorn-lzorn/"

def enable_windows_ansi_colors():
    """在Windows上启用ANSI颜色支持"""
    if sys.platform.startswith('win'):
        try:
            import colorama
            colorama.init()
        except ImportError:
            # 如果没有colorama，尝试启用Windows 10+ 的ANSI支持
            try:
                import ctypes
                kernel32 = ctypes.windll.kernel32
                kernel32.SetConsoleMode(kernel32.GetStdHandle(-11), 7)
            except:
                pass

def log_info(message):
    """输出信息日志"""
    print(f"{Colors.BLUE}[INFO]{Colors.NC} {message}")

def log_success(message):
    """输出成功日志"""
    print(f"{Colors.GREEN}[SUCCESS]{Colors.NC} {message}")

def log_warning(message):
    """输出警告日志"""
    print(f"{Colors.YELLOW}[WARNING]{Colors.NC} {message}")

def log_error(message):
    """输出错误日志"""
    print(f"{Colors.RED}[ERROR]{Colors.NC} {message}")

def run_git_command(command):
    """执行git命令并返回结果"""
    try:
        result = subprocess.run(
            command, 
            shell=True, 
            capture_output=True, 
            text=True,
            timeout=30
        )
        return result.returncode == 0, result.stdout.strip(), result.stderr.strip()
    except subprocess.TimeoutExpired:
        return False, "", "命令执行超时"
    except Exception as e:
        return False, "", str(e)

def is_git_repository():
    """检查当前目录是否是git仓库"""
    success, _, _ = run_git_command("git rev-parse --git-dir")
    return success

def remote_repository_exists(repo_url):
    """检查远程仓库是否存在"""
    log_info("检查远程仓库是否存在...")
    success, _, error = run_git_command(f'git ls-remote "{repo_url}"')
    if not success:
        log_warning(f"远程仓库 '{repo_url}' 不存在或无法访问")
        if error:
            log_warning(f"错误详情: {error}")
    return success

def get_current_remotes():
    """获取当前的remote配置"""
    success, output, _ = run_git_command("git remote -v")
    if success:
        return output
    return ""

def origin_exists():
    """检查origin remote是否已存在"""
    success, _, _ = run_git_command("git remote get-url origin")
    return success

def add_origin_remote(repo_url):
    """添加新的origin remote"""
    success, _, error = run_git_command(f'git remote add origin "{repo_url}"')
    if success:
        log_success("成功添加origin remote")
    else:
        log_error(f"添加origin remote失败: {error}")
    return success

def update_origin_remote(repo_url):
    """更新existing origin remote"""
    success, _, error = run_git_command(f'git remote set-url origin "{repo_url}"')
    if success:
        log_success("成功更新origin remote URL")
    else:
        log_error(f"更新origin remote URL失败: {error}")
    return success

def test_connection(repo_url):
    """测试与远程仓库的连接"""
    log_info(f"测试连接到 {repo_url} ...")
    success, _, error = run_git_command("git ls-remote origin")
    if success:
        log_success("连接测试成功！")
    else:
        log_warning(f"连接测试失败: {error}")
    return success

def create_argument_parser():
    """创建命令行参数解析器"""
    parser = argparse.ArgumentParser(
        description="Git Remote仓库更换脚本",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=f"""
示例:
  {sys.argv[0]} MyProject
  {sys.argv[0]} MyProject https://github.com/username/
  {sys.argv[0]} --test MyProject

注意:
  - 脚本会自动检查远程仓库是否存在
  - 如果仓库不存在，脚本不会进行任何操作
  - 默认GitHub路径为: {DEFAULT_GITHUB_PATH}
        """
    )
    
    parser.add_argument(
        "repo_name",
        help="要更换的仓库名称"
    )
    
    parser.add_argument(
        "github_path",
        nargs="?",
        default=DEFAULT_GITHUB_PATH,
        help=f"GitHub路径 (默认: {DEFAULT_GITHUB_PATH})"
    )
    
    parser.add_argument(
        "--test",
        action="store_true",
        help="执行完成后测试与远程仓库的连接"
    )
    
    parser.add_argument(
        "--dry-run",
        action="store_true",
        help="只显示将要执行的操作，不实际执行"
    )
    
    return parser

def main():
    """主函数"""
    # 启用Windows ANSI颜色支持
    enable_windows_ansi_colors()
    
    # 解析命令行参数
    parser = create_argument_parser()
    args = parser.parse_args()
    
    repo_name = args.repo_name
    github_path = args.github_path
    
    # 确保GitHub路径以/结尾
    if not github_path.endswith('/'):
        github_path += '/'
    
    # 构建完整的仓库URL
    repo_url = f"{github_path}{repo_name}.git"
    
    print(f"{Colors.PURPLE}=== Git Remote仓库更换脚本 ==={Colors.NC}")
    log_info(f"仓库名: {repo_name}")
    log_info(f"GitHub路径: {github_path}")
    log_info(f"完整URL: {repo_url}")
    
    if args.dry_run:
        log_info("干运行模式：只显示操作，不实际执行")
    
    # 检查是否在git仓库中
    if not is_git_repository():
        log_error("当前目录不是Git仓库")
        return 1
    
    # 检查远程仓库是否存在
    if not remote_repository_exists(repo_url):
        log_info("跳过操作，不进行任何更改")
        return 0
    
    log_success("远程仓库存在，继续执行...")
    
    # 显示当前的remote配置
    current_remotes = get_current_remotes()
    if current_remotes:
        log_info("当前remote配置:")
        for line in current_remotes.split('\n'):
            print(f"  {line}")
    
    if args.dry_run:
        if origin_exists():
            log_info(f"[DRY-RUN] 将更新origin remote到: {repo_url}")
        else:
            log_info(f"[DRY-RUN] 将添加origin remote: {repo_url}")
        return 0
    
    # 添加或更新origin remote
    if origin_exists():
        log_info("更新existing origin remote...")
        if not update_origin_remote(repo_url):
            return 1
    else:
        log_info("添加新的origin remote...")
        if not add_origin_remote(repo_url):
            return 1
    
    # 显示更新后的remote配置
    print()
    updated_remotes = get_current_remotes()
    if updated_remotes:
        log_info("更新后的remote配置:")
        for line in updated_remotes.split('\n'):
            print(f"  {line}")
    
    # 可选：测试连接
    if args.test:
        print()
        test_connection(repo_url)
    
    print()
    log_success("Remote仓库更换完成！")
    return 0

if __name__ == "__main__":
    try:
        exit_code = main()
        sys.exit(exit_code)
    except KeyboardInterrupt:
        print(f"\n{Colors.YELLOW}操作被用户中断{Colors.NC}")
        sys.exit(1)
    except Exception as e:
        log_error(f"发生未预期的错误: {e}")
        sys.exit(1)