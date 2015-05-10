# none of that stupid bash header crap!

function tmux
    command tmux -S ~/.tmux.socket $argv
end

function tmux-print-session
    tmux display-message -p '#S'
end

##################
#    SETTINGS    #
##################

set -U main_session "main"
set -U projects_dir ~/src

# starts a tmux session, requires a client_session argument
#
# - will autostart main_session (presistant background session)
#   if this is the first time run since bootup 
# - starts client_session if one does not exist
# - attachs to the client_session
function tmux-start				\
    --description "start a new tmux session"	\
    --argument-names "client_session"

    if [ $TMUX ]; echo "tmux-start does not support recursive tmux"; return 1; end
    if [ ! $client_session ]; echo "please give a client session name"; return 1; end

    # auto start main if doesn't exist
    if not tmux has-session -t $main_session ^/dev/null
	echo "making new main session"
	tmux new-session -s $main_session -c $HOME -n "LOCAL" -d
	tmux send-keys -t $main_session "tmux-setup-main" C-m
    end

    # start client session if doesn't exist
    if not tmux has-session -t $client_session ^/dev/null
	echo "making new main session"
	tmux new-session -s $client_session -c $HOME -n "LOCAL" -d
	tmux send-keys -t $client_session "tmux-setup-client" C-m
    end

    tmux attach -t $client_session
end

#########################
#    PANEFUl CONFIGS    #
#########################

function tmux-windows-cmd						\
    --description "generates a generic window, defaulting to home" 	\
    --argument-names "dir"

    if [ ! $dir ]; set dir $HOME; end
	# defaults directory to home if none is specified

    echo "creating new cmd window - default location: $dir"

    tmux new-window -n "CMD" -c $dir
end

# used to generate generic workspace windows, defaulting a specific project directory
function tmux-windows-wksp				\
    --description "generates a workspace window"	\
    --argument-names "project_name" "wksp_type"

    if [ ! $project_name ];
	echo "please enter a project name"; return 1;
    end

    # decided I wanted to central projects under the ~/src directory
    # this checks to make sure the directory exist for the project option
    set -l project_dir "$projects_dir/$project_name"
    if [ ! -d $project_dir ]
	echo "project $project_name does not have a directory under ~/src"; return 1
    end

    echo "creating new workspace window - project $project_name, wksp_type $wksp_type"

    if [ "$wksp_type" = "test" ]
	set -l window_name "$project_name [t]"

	# test workspaces get a vertical split,
	# then a horizontal on the right side
	tmux new-window -n "$window_name" -c $project_dir
	tmux split-window -t "$window_name" -h -p 60 -c $project_dir
	tmux split-window -t "$window_name" -v -p 50 -c $project_dir
    else
	# everything else is just a full pane
	tmux new-window -n "$project_name [s]" -c $project_dir
    end
end

#########################
#    SESSION CONFIGS    #
#########################

# initializes the main_session with some default windows I generally like
function tmux-setup-main					\
    --description "run to setup default windows in main"

    if [ $main_setup ]; return 1; end;

    tmux-windows-cmd
    tmux-windows-wksp linux-stable src
    tmux-windows-wksp linux-stable test

    set -g main_setup "complete"
end

# initializes the new client_session to link all windows from main_session
function tmux-setup-client
    tmux-link-windows 
end

# links all windows from src_session (default $main_session) -> current_session
function tmux-link-windows						\
	--description "links to all windows from <src> to current"	\
	--argument-names "src_session"

    # src_session defaults to $main_session" if not given
    # dst_session is always the current session
    if [ ! $src_session ]; set src_session $main_session; end
    set -l dst_session (tmux-print-session)

    echo "linking in all windows from: $src_session"

    # loops over windows (1..N-1) linking each from main to current
    # 	- skips window 0, which is to be reserved for non shared usage
    set num_windows (count (tmux list-windows -t $main_session))
    for i in (seq (math "$num_windows-1")) 
	tmux link-window -dk -s $src_session:$i -t $dst_session:$i
    end
end

# called from client_session to initialize a new window in main,
# and then links it into the client_session
function tmux-new-window						\
    --description "starts window in main_session and links here"	\
    --argument-names "window_type"

    if [ ! $window_type ]
	echo "tmux-new-window needs to be given a type"; return;
    end

    set window_func "tmux-windows-$window_type"
    if not functions -q $window_func
	echo "window type: $window_type is not a valid type"; return
    end

    set window_params $argv[2..-1]
    set client_session (tmux-print-session)

    tmux send-keys -t $main_session:0 "$window_func $window_params" C-m
    tmux-link-windows
end

