"" Vim-Plug Initialisation
if empty(glob('~/.vim/autoload/plug.vim'))
	  silent !curl -fLo ~/.vim/autoload/plug.vim --create-dirs
	      \ https://raw.githubusercontent.com/junegunn/vim-plug/master/plug.vim
	    autocmd VimEnter * PlugInstall --sync | source $MYVIMRC
endif

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
colorscheme gruvbox
set background=dark
set ttyfast
set number
set relativenumber

"" Editing Setting
inoremap tk <ESC>
set autoindent
set smartindent
set tabstop=4
set softtabstop=4
set shiftwidth=4
set cursorline
set showmatch

"" Key Mappings
nnoremap <space> za

"" Vanilla brackets autocomplete
inoremap <C-n> <esc>/[)}"'\]>]<CR>:nohl<CR>a
inoremap " ""<left>
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
