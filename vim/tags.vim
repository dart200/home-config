set notagrelative

let s:sourcedirs = "."

let s:cscope = "cscope -b -q -k -i-"
let s:ctags = "ctags --langmap=C++: --langmap=C:.c.h --languages=C --fields=+S --c-kinds=-m"

"let s:ctags = s:ctags . ' --c-kinds=+p --fields=+iaS --extra=+q'
"let s:ctags = "ctags --langmap=C++:.c.h --fields=+S --extra=+q"

func! TagFile()
	"substitute(bufname("%"), '.*/\zs', '.', '') . ".tags"
	return substitute(bufname("%"), '\(.*/\|^\)\zs', '.', '') . ".tags"
endfunc

func! ToggleTags()
	let l:t = TagFile()

	if (filereadable(l:t))
		if count(tagfiles(), "tags")
			let &l:tags = l:t
		else
			let &l:tags = l:t . ",tags"
		endif
	endif
endfunc

map <expr> <F12> ToggleTags()

func! MakeCscope()
	if getftime(bufname("%")) > getftime("cscope.out") + 600
		call system('(flock -n 9 || exit ; '
			  \.'	git ls-files --exclude-standard ' . s:sourcedirs
			  \.'	|cscope -b -q -k -i- '
			  \.') 9>.cscope.lock &')
	endif
endfunc

func! MakeAllTags()
	let l:ctags = s:ctags . " -R "

	if getftime(bufname("%")) > getftime("tags") + 600
		call system('(flock -n 9 || exit ; '
			  \.	l:ctags  . s:sourcedirs
			  \.') 9>.ctags.lock &')
	endif
endfunc

func! MakeLocalTags()
	let l:t = TagFile()
	let l:ctags = s:ctags . ' --c-kinds=+p -f ' . l:t

	if getftime(bufname("%")) > getftime(l:t)
		redir => l:include
		silent! checkpath!
		redir END

		let l:includes = split(l:include, "\n")
		let l:includes[0] = expand("%")

		call filter(l:includes, 'v:val !~ "\\(NOT FOUND\\|(Already listed)\\| -->\\)"')
		call system(l:ctags . ' '. join(l:includes) . " &")
	endif
endfunc

func! LinuxStuff()
	if !filereadable("Kbuild") || !filereadable("Makefile")
		return
	endif

	let s:sourcedirs = "arch/x86 block crypto drivers fs include init ipc kernel lib mm net security virt"

	setlocal path=.,include,include/uapi,arch/x86/include

	let l:make = "make"

	if filereadable(".linux/.config")
		let l:make = l:make . " O=.linux"
	endif

	let &l:makeprg = l:make . " %<.o"

	augroup LinuxStuff
		au!
		au BufRead,BufWritePost	* call MakeAllTags()
	augroup end
endfunc

func! InitTags()
	let &l:tags = TagFile()

	call LinuxStuff()
	call MakeCscope()
	call MakeAllTags()
	call MakeLocalTags()

	augroup tags
		au BufReadPost,BufWritePost	<buffer> call MakeCscope()
		au BufReadPost,BufWritePost	<buffer> call MakeAllTags()
		au BufReadPost,BufWritePost	<buffer> call MakeLocalTags()
	augroup end
endfunc

augroup inittags
	au!
	au BufWritePost ~/.vim/tags.vim	  source ~/.vim/tags.vim

	au FileType			c call InitTags()
augroup end


" Csfind()
"
" This function uses :try and related commands which were first introduced
" at vim-6.2, so any application should check for v:version >= 602 before
" calling it.
"
" When errors occur within a function, vim prints the function name and
" line number as well as the error message from the command that failed.
" The user doesn't care about this, so this function catches _all_ errors
" from :cscope so that the user will see only the error messages from
" :cscope itself.

command! -nargs=+ Csfind call Csfind("cscope", <f-args>)
command! -nargs=+ SCsfind call Csfind("vertical scscope", <f-args>)

function! Csfind(cmd, querytype, name)
	try
		execute a:cmd . " find " . a:querytype . " " . a:name
	catch /E567/                    " 'no cscope connections'
		try
			if cscope_connection()
				cscope reset
			else
				cscope add cscope.out
			endif
		catch /.*/
			" Note:  The perror() message
			"    cs_read_prompt EOF: Error 0
			" currently (2004-02-20) hides the more-informative message
			"    E609: Cscope error: cscope: cannot read file version from file cscope.out
			"
			call s:EchoException()
			return
		endtry
		try
			execute a:cmd . " find " . a:querytype . " " . a:name
		catch /.*/                  " Any error.
			call s:EchoException()
		endtry
	catch /.*/                      " Any other error.
		call s:EchoException()
	endtry
endfunction

function! s:EchoException()
	if &errorbells
		normal \<Esc>               " Generate a bell
	endif
	echohl ErrorMsg
	echo matchstr(v:exception, ':\zs.*')
	echohl None
endfunction

nmap <C-\>s :Csfind s <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>g :Csfind g <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>c :Csfind c <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>t :Csfind t <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>e :Csfind e <C-R>=expand("<cword>")<CR><CR>
nmap <C-\>f :Csfind f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-\>i :Csfind i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-\>d :Csfind d <C-R>=expand("<cword>")<CR><CR>

nmap <C-Space>s :tab Cs find s <C-R>=expand("<cword>")<CR><CR>
nmap <C-Space>g :tab Csfind g <C-R>=expand("<cword>")<CR><CR>
nmap <C-Space>c :tab Csfind c <C-R>=expand("<cword>")<CR><CR>
nmap <C-Space>t :tab Csfind t <C-R>=expand("<cword>")<CR><CR>
nmap <C-Space>e :tab Csfind e <C-R>=expand("<cword>")<CR><CR>
nmap <C-Space>f :tab Csfind f <C-R>=expand("<cfile>")<CR><CR>
nmap <C-Space>i :tab Csfind i ^<C-R>=expand("<cfile>")<CR>$<CR>
nmap <C-Space>d :tab Csfind d <C-R>=expand("<cword>")<CR><CR>
