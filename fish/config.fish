set -g -x PATH ~/bin $PATH
set -g -x fish_greeting ''

if [ $TERM =! "screen-256color" ]
    set -g -x TERM xterm-256color
end

source ~/.config/fish/tmux-functions.fish
