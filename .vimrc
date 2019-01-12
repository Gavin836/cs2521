call plug#begin('~/.vim/plugged')
Plug 'morhetz/gruvbox'
Plug 'vim-syntastic/syntastic'
call plug#end()

"" Synatastic
set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

"" Visual Setting
set background=dark
set ttyfast

"" Editing Setting
set autoindent
set smartindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set cursorline
set showmatch

"" Map tab to autocomplete
imap <Tab> <C-P>

"" Vanilla brackets autocomplete
noremap " ""<left>
inoremap ' ''<left>
inoremap ( ()<left>
inoremap [ []<left>
inoremap { {}<left>
inoremap {<CR> {<CR>}<ESC>O
inoremap {;<CR> {<CR>};<ESC>O

"" Search settings
set wildmenu
set incsearch
set hlsearch

