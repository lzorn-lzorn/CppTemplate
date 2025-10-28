#!/bin/bash

# 跨平台Git Remote仓库更换脚本 (Shell版本)
# 用法: ./change-remote.sh <仓库名> [GitHub路径]
# 
# 参数:
#   仓库名: 必需，要更换的仓库名称
#   GitHub路径: 可选，默认为 https://github.com/lzorn-lzorn/
#
# 示例:
#   ./change-remote.sh MyProject
#   ./change-remote.sh MyProject https://github.com/username/
#

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 默认GitHub路径
DEFAULT_GITHUB_PATH="https://github.com/lzorn-lzorn/"

# 显示使用帮助
show_help() {
    echo -e "${BLUE}Git Remote仓库更换脚本${NC}"
    echo ""
    echo "用法: $0 <仓库名> [GitHub路径]"
    echo ""
    echo "参数:"
    echo "  仓库名      必需，要更换的仓库名称"
    echo "  GitHub路径  可选，默认为 ${DEFAULT_GITHUB_PATH}"
    echo ""
    echo "示例:"
    echo "  $0 MyProject"
    echo "  $0 MyProject https://github.com/username/"
    echo ""
    echo "选项:"
    echo "  -h, --help  显示此帮助信息"
    echo ""
}

# 日志函数
log_info() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

log_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

log_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

log_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# 检查参数
if [ "$1" = "-h" ] || [ "$1" = "--help" ]; then
    show_help
    exit 0
fi

if [ $# -lt 1 ]; then
    log_error "缺少必需参数"
    echo ""
    show_help
    exit 1
fi

# 获取参数
REPO_NAME="$1"
GITHUB_PATH="${2:-$DEFAULT_GITHUB_PATH}"

# 确保GitHub路径以/结尾
if [[ ! "$GITHUB_PATH" == */ ]]; then
    GITHUB_PATH="${GITHUB_PATH}/"
fi

# 构建完整的仓库URL
REPO_URL="${GITHUB_PATH}${REPO_NAME}.git"

log_info "开始更换remote仓库..."
log_info "仓库名: $REPO_NAME"
log_info "GitHub路径: $GITHUB_PATH"
log_info "完整URL: $REPO_URL"

# 检查是否在git仓库中
if ! git rev-parse --git-dir > /dev/null 2>&1; then
    log_error "当前目录不是Git仓库"
    exit 1
fi

# 检查远程仓库是否存在
log_info "检查远程仓库是否存在..."

# 使用git ls-remote检查仓库是否存在
if ! git ls-remote "$REPO_URL" > /dev/null 2>&1; then
    log_warning "远程仓库 '$REPO_URL' 不存在或无法访问"
    log_info "跳过操作，不进行任何更改"
    exit 0
fi

log_success "远程仓库存在，继续执行..."

# 显示当前的remote配置
log_info "当前remote配置:"
git remote -v

# 检查origin是否已存在
if git remote get-url origin > /dev/null 2>&1; then
    log_info "更新existing origin remote..."
    if git remote set-url origin "$REPO_URL"; then
        log_success "成功更新origin remote URL"
    else
        log_error "更新origin remote URL失败"
        exit 1
    fi
else
    log_info "添加新的origin remote..."
    if git remote add origin "$REPO_URL"; then
        log_success "成功添加origin remote"
    else
        log_error "添加origin remote失败"
        exit 1
    fi
fi

# 显示更新后的remote配置
echo ""
log_info "更新后的remote配置:"
git remote -v

# 可选：测试连接
echo ""
read -p "是否测试与新remote的连接? (y/N): " -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    log_info "测试连接到 $REPO_URL ..."
    if git ls-remote origin > /dev/null 2>&1; then
        log_success "连接测试成功！"
    else
        log_warning "连接测试失败，请检查URL和网络连接"
    fi
fi

log_success "Remote仓库更换完成！"