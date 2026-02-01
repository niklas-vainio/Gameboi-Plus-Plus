# All-in-one install script

red="\033[1;91m"; dim="\033[0;90m"; green="\033[0;32m"; reset="\033[0m"

# Alert the user if they are missing required tools
command -v g++ >/dev/null 2>&1 || echo -e "${red}Error: g++ is not installed - on MacOS, try ${dim}xcode-select --install${red}${reset}"
command -v cmake >/dev/null 2>&1 || echo -e "${red}Error: g++ is not installed - on MacOS, try ${dim}brew install cmake${red}${reset}"

# Pull in submodules
git submodule update --init --recursive

# SDL_ttf keeps external deps in external/ and provides a helper script.
# (On Windows there is external/Get-GitModules.ps1; on *nix/mac there is external/download.sh)
if [[ -x "external/SDL_ttf/external/download.sh" ]]; then
  echo -e "${dim}Fetching SDL_ttf external deps...${reset}"
  (cd "external/SDL_ttf/external" && ./download.sh)
fi

echo
echo "${green}✅ Setup complete! Run ${dim}make${green} to compile the project!${reset}"
echo