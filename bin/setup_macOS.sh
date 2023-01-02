#!/bin/sh

echo "::group::install dependencies"
export HOMEBREW_NO_AUTO_UPDATE=1
brew install wxwidgets
echo "::endgroup::"
