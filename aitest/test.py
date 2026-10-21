# model_diagnostic.py
import sys
import os
import hashlib
 
def check_model_health(model_path):
    """快速检查模型健康状况"""
    print("🔍 模型健康检查开始...")
    
    # 1. 检查文件是否存在
    if not os.path.exists(model_path):
        print(f"❌ 错误：文件不存在 - {model_path}")
        return False
    
    # 2. 检查文件大小
    file_size = os.path.getsize(model_path) / (1024*1024)  # MB
    print(f"✅ 文件存在，大小: {file_size:.2f} MB")
    
    # 3. 检查文件扩展名
    valid_extensions = ['.pth', '.pt', '.h5', '.pb', '.bin', '.safetensors']
    ext = os.path.splitext(model_path)[1]
    if ext not in valid_extensions:
        print(f"⚠️  警告：非常规扩展名 {ext}")
    
    # 4. 计算文件哈希（可选）
    try:
        with open(model_path, 'rb') as f:
            file_hash = hashlib.md5(f.read()).hexdigest()
        print(f"📊 文件MD5: {file_hash[:8]}...")
    except Exception as e:
        print(f"⚠️  无法计算哈希: {e}")
    
    return True
 
if __name__ == "__main__":
    model_path = input("请输入模型路径: ").strip()
    check_model_health(model_path)