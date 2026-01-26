# All-in-one install script

# Alert the user if they are missing required tools
command -v g++ >/dev/null 2>&1 || echo "\e[1;91mError: g++ is not installed - on MacOS, try \e[0;90mxcode-select --install\e[1;91m"
command -v cmake >/dev/null 2>&1 || echo "\e[1;91mError: g++ is not installed - on MacOS, try \e[0;90mbrew install cmake\e[1;91m"

# Pull in submodules
git submodule update --init --recursive

echo
echo "\e[0;32m✅ Setup complete! Run \e[0;90mmake\e[0;32m to compile the project!"
echo