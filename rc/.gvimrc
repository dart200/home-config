"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => General
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set number           " show line numbers

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Remove gvim gui options
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
set guioptions-=m    " remove menu bar
set guioptions-=T    " remove tool bar
set guioptions-=r    " remove right scroll
set guioptions-=R    " remove right scroll
set guioptions-=l    " remove left scroll
set guioptions-=L    " remove left scroll

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Window's style copy paste to global buffer
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
vmap <C-S-C> "+y 
nmap <C-S-V> "+gP
imap <C-S-V> <ESC>"+gPa
vmap <C-S-X> "+x

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Ctr-direction window navigation
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
map <C-left> <C-w>h
map <C-down> <C-w>j
map <C-up> <C-w>k
map <C-right> <C-w>l

imap <C-left> <ESC><right><C-w>hi
imap <C-down> <ESC><right><C-w>ji
imap <C-up> <ESC><right><C-w>ki
imap <C-right> <ESC><right><C-w>li
