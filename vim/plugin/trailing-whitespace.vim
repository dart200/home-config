" Highlight EOL whitespace, http://vim.wikia.com/wiki/Highlight_unwanted_spaces
let fileTypes = ['*.c', '*.cpp', '*.h', '*.py', '*.dc']

highlight ExtraWhitespace ctermbg=darkred guibg=#382424
autocmd ColorScheme *.c,*.h,*.cpp,*.dc,*.py highlight ExtraWhitespace ctermbg=red guibg=red
autocmd BufWinEnter *.c,*.h,*.cpp,*.dc,*.py match ExtraWhitespace /\s\+$\| \+\ze\t/ 
" the above flashes annoyingly while typing, be calmer in insert mode
autocmd InsertEnter *.c,*.h,*.cpp,*.dc,*.py match ExtraWhitespace /\s\+\%#\@<!$/
autocmd InsertLeave *.c,*.h,*.cpp,*.dc,*.py match ExtraWhitespace /\s\+$\| \+\ze\t/ 

function! s:FixWhitespace(line1,line2)
    let l:save_cursor = getpos(".")
    silent! execute ':' . a:line1 . ',' . a:line2 . 's/\s\+$//'
    call setpos('.', l:save_cursor)
endfunction

" Run :FixWhitespace to remove end of line white space.
command! -range=% FixWhitespace call <SID>FixWhitespace(<line1>,<line2>)
