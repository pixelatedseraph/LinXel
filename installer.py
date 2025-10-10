#!/usr/bin/env python3
import os
import shutil
from pathlib import Path
import stat
import argparse

# --- Setup paths ---
home = Path.home()
bin_dir = home / ".local/bin"
bin_dir.mkdir(parents=True, exist_ok=True)

binary_name = "linxel"
src = Path("./linxel")
dst = bin_dir / binary_name

# Detect shell RC file
shell = os.environ.get("SHELL", "")
if "zsh" in shell:
    rc_file = home / ".zshrc"
else:
    rc_file = home / ".bashrc"

path_line = f'export PATH="{bin_dir}:$PATH"\n'

def add_path_to_rc():
    if path_line not in rc_file.read_text():
        with open(rc_file, "a") as f:
            f.write("\n# Added by linxel installer\n")
            f.write(path_line)
        print(f"Added {bin_dir} to PATH in {rc_file}. Reload shell or run: source {rc_file}")

def remove_path_from_rc():
    if path_line in rc_file.read_text():
        lines = rc_file.read_text().splitlines()
        with open(rc_file, "w") as f:
            for line in lines:
                if line != path_line.strip() and line != "# Added by linxel installer":
                    f.write(line + "\n")
        print(f"Removed {bin_dir} from PATH in {rc_file}")

def install():
    if not src.exists():
        print(f"Source binary {src} not found!")
        return
    shutil.copy2(src, dst)
    dst.chmod(dst.stat().st_mode | stat.S_IEXEC)
    add_path_to_rc()
    print(f"Installed {binary_name}! Happy Hacking! ")

def uninstall():
    if dst.exists():
        dst.unlink()
        print(f"🗑️ Removed {binary_name} binary from {bin_dir}")
    remove_path_from_rc()
    print(" Uninstall complete.")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Install or uninstall linxel CLI")
    parser.add_argument("--uninstall", action="store_true", help="Remove linxel")
    args = parser.parse_args()

    if args.uninstall:
        uninstall()
    else:
        install()
