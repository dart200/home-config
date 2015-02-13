if exists("did_load_filetypes")
   finish
endif

augroup filetypedetect
   au! BufNewFile,BufRead TODO setf todo
augroup END
