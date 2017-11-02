# none of that stupid bash header crap!

function tmux
    command tmux -S ~/.tmux.socket $argv
end
