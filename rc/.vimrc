"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Vundle
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

set nocompatible              " be iMproved
filetype off                  " required temp for vundle

" set the runtime path to include Vundle and initialize
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
" alternatively, pass a path where Vundle should install plugins
"call vundle#begin('~/some/path/here')

"*** PLUGINS START ***"
Plugin 'VundleVim/Vundle.vim' 	" let Vundle manage Vundle, required
Plugin 'dag/vim-fish' 		" fishies!
Plugin 'rust-lang/rust.vim'	" Rust
Plugin 'cespare/vim-toml'	" Tom's Obvious Minimal Language
"*** PLUGINS END ***"

" All of your Plugins must be added before the following line
call vundle#end()            " required
filetype plugin indent on    " required

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Sets how many lines of history VIM has to remember
set history=700

" Enable filetype plugins
filetype plugin on
filetype indent on

" always show status bar
set laststatus=2

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => VIM user interface
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Always show current position
set ruler

" Configure backspace so it acts as it should act
set backspace=eol,start,indent
set whichwrap+=<,>,h,l

set hlsearch "Highlight search results
set ignorecase "Ignore case when searching
set smartcase " When searching try to be smart about cases
set showmatch " Show matching brackets when text indicator is over them
set mat=2 " How many tenths of a second to blink when matching brackets

" folding
set foldmethod=syntax
set foldnestmax=1

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Kent's scripts
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

if filereadable($HOME."/scripts/vim/vimrc")
    source ~/scripts/vim/vimrc
endif

if filereadable($HOME."/scripts/vim/tags.vim")
    source ~/scripts/vim/tags.vim
endif

if filereadable($HOME."/scripts/vim/git.vim")
    source ~/scripts/vim/git.vim 
endif

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Colors and Fonts
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

" Enable syntax highlighting
syntax enable
set background=dark
color molokai  

set encoding=utf8 " Set utf8 as standard encoding and en_US as the standard language
set ffs=unix,dos,mac " Use Unix as the standard file type

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Text, tab and indent related
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"set expandtab        " expand tabs
set smarttab          
set shiftwidth=4
set tabstop=4
set softtabstop=4
set expandtab

"special kernel style settings
au FileType c,h set noexpandtab
au FileType c,h set shiftwidth=8

"special styling for mdwn
au FileType markdown set noexpandtab
au FileType markdown set shiftwidth=8

"turn off folding for git commit
au FileType git* set nofoldenable

"color dc files"
au BufRead,BufNewFile *.dc set filetype=python

"detect *.rs as rust file
au BufNewFile,BufRead *.rs   set filetype=rust

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => autoreload files if changed
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set autoread
au BufEnter,BufWinEnter,CursorHold * :checktime

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Window's style copy paste to global buffer
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
vmap <C-S-C> "+y 
nmap <C-S-V> "+gP
imap <C-S-V> <ESC>"+gPa
vmap <C-S-X> "+x

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => custom shortcuts
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
"swap redo and replace
nnoremap <C-r> r
nnoremap r <C-r> 

"swap <shift> V with v (v will now select whole line)
noremap V v
noremap v V

"scroll using Ctr-Up or Ctr-Down
nmap <C-Up> <C-U> 
nmap <C-Down> <C-D>
set scroll=1
