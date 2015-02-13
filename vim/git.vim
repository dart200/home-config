
func! MakeScratch()
	setlocal buftype=nofile
	setlocal bufhidden=wipe
	setlocal noswapfile
	setlocal nomodifiable
"	setlocal nobuflisted
endfunc

func! Show(...)
	setlocal splitright
	let l:fname = exists("b:fname") ? b:fname : bufname("%")
	let l:n = exists("a:1") ? a:1 : ""

	let l:cmd = "read! git show " . l:n . ":" . l:fname
	let l:ftype = &filetype
	let l:rev = system("git rev-parse --verify --short " . l:n)
	let l:rev = strpart(l:rev, 0, stridx(l:rev, "\n")) . " " . l:n
	vnew +exe\ l:cmd

	call MakeScratch()
	let b:fname = l:fname
	let &l:statusline=l:rev . "%f\ %h%m%r%=%-14.(%l,%c%V%)\ %P"
	let &l:filetype=l:ftype
endfunc

func! Diff(...)
	let l:foldmethod = &foldmethod
	let l:bufnr = bufnr('%')

	call Show(exists("a:1") ? a:1 : "HEAD")

	"exe 'au BufDelete <buffer> buffer ' . l:bufnr . '|diffoff  |set foldmethod=' . l:foldmethod
	exe 'au BufDelete <buffer> windo diffoff  |set foldmethod=' . l:foldmethod
	diffthis
	wincmd p
	diffthis
endfunc

command! -nargs=? Diff call Diff(<f-args>)
command! -nargs=? Show  call Show(<f-args>)

func! Blame()
endfunc

func! GitBlameLine()
	if &previewwindow
		return
	endif

	let l:bufnr = bufnr('%')

	let b:blameline = line('.')
	let l:cmd = 'read! git log -n1 `git blame --root -L ' .
				\b:blameline . ",+1 " . bufname("%") .
				\'|cut -d\  -f1`'

	silent! wincmd P
	if ! &previewwindow
		pedit
	endif
	wincmd P
	enew

	silent! exe l:cmd

	call MakeScratch()
	setlocal filetype=git

	exe 'au BufDelete <buffer> au! blame * <buffer=' . l:bufnr . '>'

	wincmd p
endfunc

func! BlameLineChanged()
	if b:blameline != line('.')
		call GitBlameLine()
	endif
endfunc

func! BlameLine()
	call GitBlameLine()

	augroup blame
		au!
		au CursorMoved,CursorMovedI <buffer> call BlameLineChanged()
	augroup END
endfunc

nmap <C-g>s :call BlameLine() <CR>
