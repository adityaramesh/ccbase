let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <S-Tab> <Plug>SuperTabBackward
inoremap <silent> <C-Tab> =UltiSnips#ListSnippets()
inoremap <Right> <Nop>
inoremap <Left> <Nop>
inoremap <Down> <Nop>
inoremap <Up> <Nop>
map! <D-v> *
snoremap <silent>  c
xnoremap <silent> 	 :call UltiSnips#SaveLastVisualSelection()gvs
snoremap <silent> 	 :call UltiSnips#ExpandSnippetOrJump()
nnoremap <silent>  :nohl
snoremap  "_c
vnoremap < <gv
xnoremap > >gv
snoremap > >gv
onoremap <silent> Ar :call targets#omap('[]', 'seekselectp expand')
onoremap <silent> Anr :call targets#omap('[]', 'nextp selectp expand')
onoremap <silent> Alr :call targets#omap('[]', 'lastp selectp expand')
xnoremap <silent> <expr> A targets#uppercaseXmap('A')
onoremap <silent> Ala :call targets#omap('<>', 'lastp selectp expand')
onoremap <silent> Ana :call targets#omap('<>', 'nextp selectp expand')
onoremap <silent> Aa :call targets#omap('<>', 'seekselectp expand')
onoremap <silent> AL$ :call targets#omap('$', 'double last select expand')
onoremap <silent> AN$ :call targets#omap('$', 'double next select expand')
onoremap <silent> Al$ :call targets#omap('$', 'last select expand')
onoremap <silent> An$ :call targets#omap('$', 'next select expand')
onoremap <silent> A$ :call targets#omap('$', 'seekselect expand')
onoremap <silent> AL& :call targets#omap('&', 'double last select expand')
onoremap <silent> AN& :call targets#omap('&', 'double next select expand')
onoremap <silent> Al& :call targets#omap('&', 'last select expand')
onoremap <silent> An& :call targets#omap('&', 'next select expand')
onoremap <silent> A& :call targets#omap('&', 'seekselect expand')
onoremap <silent> AL| :call targets#omap('|', 'double last select expand')
onoremap <silent> AN| :call targets#omap('|', 'double next select expand')
onoremap <silent> Al| :call targets#omap('|', 'last select expand')
onoremap <silent> An| :call targets#omap('|', 'next select expand')
onoremap <silent> A| :call targets#omap('|', 'seekselect expand')
onoremap <silent> AL\ :call targets#omap('\', 'double last select expand')
onoremap <silent> AN\ :call targets#omap('\', 'double next select expand')
onoremap <silent> Al\ :call targets#omap('\', 'last select expand')
onoremap <silent> An\ :call targets#omap('\', 'next select expand')
onoremap <silent> A\ :call targets#omap('\', 'seekselect expand')
onoremap <silent> AL/ :call targets#omap('/', 'double last select expand')
onoremap <silent> AN/ :call targets#omap('/', 'double next select expand')
onoremap <silent> Al/ :call targets#omap('/', 'last select expand')
onoremap <silent> An/ :call targets#omap('/', 'next select expand')
onoremap <silent> A/ :call targets#omap('/', 'seekselect expand')
onoremap <silent> AL# :call targets#omap('#', 'double last select expand')
onoremap <silent> AN# :call targets#omap('#', 'double next select expand')
onoremap <silent> Al# :call targets#omap('#', 'last select expand')
onoremap <silent> An# :call targets#omap('#', 'next select expand')
onoremap <silent> A# :call targets#omap('#', 'seekselect expand')
onoremap <silent> AL* :call targets#omap('*', 'double last select expand')
onoremap <silent> AN* :call targets#omap('*', 'double next select expand')
onoremap <silent> Al* :call targets#omap('*', 'last select expand')
onoremap <silent> An* :call targets#omap('*', 'next select expand')
onoremap <silent> A* :call targets#omap('*', 'seekselect expand')
onoremap <silent> AL_ :call targets#omap('_', 'double last select expand')
onoremap <silent> AN_ :call targets#omap('_', 'double next select expand')
onoremap <silent> Al_ :call targets#omap('_', 'last select expand')
onoremap <silent> An_ :call targets#omap('_', 'next select expand')
onoremap <silent> A_ :call targets#omap('_', 'seekselect expand')
onoremap <silent> AL~ :call targets#omap('~', 'double last select expand')
onoremap <silent> AN~ :call targets#omap('~', 'double next select expand')
onoremap <silent> Al~ :call targets#omap('~', 'last select expand')
onoremap <silent> An~ :call targets#omap('~', 'next select expand')
onoremap <silent> A~ :call targets#omap('~', 'seekselect expand')
onoremap <silent> AL= :call targets#omap('=', 'double last select expand')
onoremap <silent> AN= :call targets#omap('=', 'double next select expand')
onoremap <silent> Al= :call targets#omap('=', 'last select expand')
onoremap <silent> An= :call targets#omap('=', 'next select expand')
onoremap <silent> A= :call targets#omap('=', 'seekselect expand')
onoremap <silent> AL- :call targets#omap('-', 'double last select expand')
onoremap <silent> AN- :call targets#omap('-', 'double next select expand')
onoremap <silent> Al- :call targets#omap('-', 'last select expand')
onoremap <silent> An- :call targets#omap('-', 'next select expand')
onoremap <silent> A- :call targets#omap('-', 'seekselect expand')
onoremap <silent> AL+ :call targets#omap('+', 'double last select expand')
onoremap <silent> AN+ :call targets#omap('+', 'double next select expand')
onoremap <silent> Al+ :call targets#omap('+', 'last select expand')
onoremap <silent> An+ :call targets#omap('+', 'next select expand')
onoremap <silent> A+ :call targets#omap('+', 'seekselect expand')
onoremap <silent> AL: :call targets#omap(':', 'double last select expand')
onoremap <silent> AN: :call targets#omap(':', 'double next select expand')
onoremap <silent> Al: :call targets#omap(':', 'last select expand')
onoremap <silent> An: :call targets#omap(':', 'next select expand')
onoremap <silent> A: :call targets#omap(':', 'seekselect expand')
onoremap <silent> AL; :call targets#omap(';', 'double last select expand')
onoremap <silent> AN; :call targets#omap(';', 'double next select expand')
onoremap <silent> Al; :call targets#omap(';', 'last select expand')
onoremap <silent> An; :call targets#omap(';', 'next select expand')
onoremap <silent> A; :call targets#omap(';', 'seekselect expand')
onoremap <silent> AL. :call targets#omap('.', 'double last select expand')
onoremap <silent> AN. :call targets#omap('.', 'double next select expand')
onoremap <silent> Al. :call targets#omap('.', 'last select expand')
onoremap <silent> An. :call targets#omap('.', 'next select expand')
onoremap <silent> A. :call targets#omap('.', 'seekselect expand')
onoremap <silent> AL, :call targets#omap(',', 'double last select expand')
onoremap <silent> AN, :call targets#omap(',', 'double next select expand')
onoremap <silent> Al, :call targets#omap(',', 'last select expand')
onoremap <silent> An, :call targets#omap(',', 'next select expand')
onoremap <silent> A, :call targets#omap(',', 'seekselect expand')
onoremap <silent> AL` :call targets#omap('`', 'quote double last select expand')
onoremap <silent> AN` :call targets#omap('`', 'quote double next select expand')
onoremap <silent> Al` :call targets#omap('`', 'quote last select expand')
onoremap <silent> An` :call targets#omap('`', 'quote next select expand')
onoremap <silent> A` :call targets#omap('`', 'quote seekselect expand')
onoremap <silent> AL' :call targets#omap('''', 'quote double last select expand')
onoremap <silent> AN' :call targets#omap('''', 'quote double next select expand')
onoremap <silent> Al' :call targets#omap('''', 'quote last select expand')
onoremap <silent> An' :call targets#omap('''', 'quote next select expand')
onoremap <silent> A' :call targets#omap('''', 'quote seekselect expand')
onoremap <silent> AL" :call targets#omap('"', 'quote double last select expand')
onoremap <silent> AN" :call targets#omap('"', 'quote double next select expand')
onoremap <silent> Al" :call targets#omap('"', 'quote last select expand')
onoremap <silent> An" :call targets#omap('"', 'quote next select expand')
onoremap <silent> A" :call targets#omap('"', 'quote seekselect expand')
onoremap <silent> Alt :call targets#omap('t', 'lastt selectp expand')
onoremap <silent> Ant :call targets#omap('t', 'nextt selectp expand')
onoremap <silent> At :call targets#omap('t', 'seekselectt expand')
onoremap <silent> Al> :call targets#omap('<>', 'lastp selectp expand')
onoremap <silent> An> :call targets#omap('<>', 'nextp selectp expand')
onoremap <silent> A> :call targets#omap('<>', 'seekselectp expand')
onoremap <silent> Al< :call targets#omap('<>', 'lastp selectp expand')
onoremap <silent> An< :call targets#omap('<>', 'nextp selectp expand')
onoremap <silent> A< :call targets#omap('<>', 'seekselectp expand')
onoremap <silent> Al] :call targets#omap('[]', 'lastp selectp expand')
onoremap <silent> An] :call targets#omap('[]', 'nextp selectp expand')
onoremap <silent> A] :call targets#omap('[]', 'seekselectp expand')
onoremap <silent> Al[ :call targets#omap('[]', 'lastp selectp expand')
onoremap <silent> An[ :call targets#omap('[]', 'nextp selectp expand')
onoremap <silent> A[ :call targets#omap('[]', 'seekselectp expand')
onoremap <silent> AlB :call targets#omap('{}', 'lastp selectp expand')
onoremap <silent> AnB :call targets#omap('{}', 'nextp selectp expand')
onoremap <silent> AB :call targets#omap('{}', 'seekselectp expand')
onoremap <silent> Al} :call targets#omap('{}', 'lastp selectp expand')
onoremap <silent> An} :call targets#omap('{}', 'nextp selectp expand')
onoremap <silent> A} :call targets#omap('{}', 'seekselectp expand')
onoremap <silent> Al{ :call targets#omap('{}', 'lastp selectp expand')
onoremap <silent> An{ :call targets#omap('{}', 'nextp selectp expand')
onoremap <silent> A{ :call targets#omap('{}', 'seekselectp expand')
onoremap <silent> Alb :call targets#omap('()', 'lastp selectp expand')
onoremap <silent> Anb :call targets#omap('()', 'nextp selectp expand')
onoremap <silent> Ab :call targets#omap('()', 'seekselectp expand')
onoremap <silent> Al) :call targets#omap('()', 'lastp selectp expand')
onoremap <silent> An) :call targets#omap('()', 'nextp selectp expand')
onoremap <silent> A) :call targets#omap('()', 'seekselectp expand')
onoremap <silent> Al( :call targets#omap('()', 'lastp selectp expand')
onoremap <silent> An( :call targets#omap('()', 'nextp selectp expand')
onoremap <silent> A( :call targets#omap('()', 'seekselectp expand')
onoremap <silent> Ir :call targets#omap('[]', 'seekselectp shrink')
onoremap <silent> Inr :call targets#omap('[]', 'nextp selectp shrink')
onoremap <silent> Ilr :call targets#omap('[]', 'lastp selectp shrink')
xnoremap <silent> <expr> I targets#uppercaseXmap('I')
onoremap <silent> Ila :call targets#omap('<>', 'lastp selectp shrink')
onoremap <silent> Ina :call targets#omap('<>', 'nextp selectp shrink')
onoremap <silent> Ia :call targets#omap('<>', 'seekselectp shrink')
onoremap <silent> IL$ :call targets#omap('$', 'double last select shrink')
onoremap <silent> IN$ :call targets#omap('$', 'double next select shrink')
onoremap <silent> Il$ :call targets#omap('$', 'last select shrink')
onoremap <silent> In$ :call targets#omap('$', 'next select shrink')
onoremap <silent> I$ :call targets#omap('$', 'seekselect shrink')
onoremap <silent> IL& :call targets#omap('&', 'double last select shrink')
onoremap <silent> IN& :call targets#omap('&', 'double next select shrink')
onoremap <silent> Il& :call targets#omap('&', 'last select shrink')
onoremap <silent> In& :call targets#omap('&', 'next select shrink')
onoremap <silent> I& :call targets#omap('&', 'seekselect shrink')
onoremap <silent> IL| :call targets#omap('|', 'double last select shrink')
onoremap <silent> IN| :call targets#omap('|', 'double next select shrink')
onoremap <silent> Il| :call targets#omap('|', 'last select shrink')
onoremap <silent> In| :call targets#omap('|', 'next select shrink')
onoremap <silent> I| :call targets#omap('|', 'seekselect shrink')
onoremap <silent> IL\ :call targets#omap('\', 'double last select shrink')
onoremap <silent> IN\ :call targets#omap('\', 'double next select shrink')
onoremap <silent> Il\ :call targets#omap('\', 'last select shrink')
onoremap <silent> In\ :call targets#omap('\', 'next select shrink')
onoremap <silent> I\ :call targets#omap('\', 'seekselect shrink')
onoremap <silent> IL/ :call targets#omap('/', 'double last select shrink')
onoremap <silent> IN/ :call targets#omap('/', 'double next select shrink')
onoremap <silent> Il/ :call targets#omap('/', 'last select shrink')
onoremap <silent> In/ :call targets#omap('/', 'next select shrink')
onoremap <silent> I/ :call targets#omap('/', 'seekselect shrink')
onoremap <silent> IL# :call targets#omap('#', 'double last select shrink')
onoremap <silent> IN# :call targets#omap('#', 'double next select shrink')
onoremap <silent> Il# :call targets#omap('#', 'last select shrink')
onoremap <silent> In# :call targets#omap('#', 'next select shrink')
onoremap <silent> I# :call targets#omap('#', 'seekselect shrink')
onoremap <silent> IL* :call targets#omap('*', 'double last select shrink')
onoremap <silent> IN* :call targets#omap('*', 'double next select shrink')
onoremap <silent> Il* :call targets#omap('*', 'last select shrink')
onoremap <silent> In* :call targets#omap('*', 'next select shrink')
onoremap <silent> I* :call targets#omap('*', 'seekselect shrink')
onoremap <silent> IL_ :call targets#omap('_', 'double last select shrink')
onoremap <silent> IN_ :call targets#omap('_', 'double next select shrink')
onoremap <silent> Il_ :call targets#omap('_', 'last select shrink')
onoremap <silent> In_ :call targets#omap('_', 'next select shrink')
onoremap <silent> I_ :call targets#omap('_', 'seekselect shrink')
onoremap <silent> IL~ :call targets#omap('~', 'double last select shrink')
onoremap <silent> IN~ :call targets#omap('~', 'double next select shrink')
onoremap <silent> Il~ :call targets#omap('~', 'last select shrink')
onoremap <silent> In~ :call targets#omap('~', 'next select shrink')
onoremap <silent> I~ :call targets#omap('~', 'seekselect shrink')
onoremap <silent> IL= :call targets#omap('=', 'double last select shrink')
onoremap <silent> IN= :call targets#omap('=', 'double next select shrink')
onoremap <silent> Il= :call targets#omap('=', 'last select shrink')
onoremap <silent> In= :call targets#omap('=', 'next select shrink')
onoremap <silent> I= :call targets#omap('=', 'seekselect shrink')
onoremap <silent> IL- :call targets#omap('-', 'double last select shrink')
onoremap <silent> IN- :call targets#omap('-', 'double next select shrink')
onoremap <silent> Il- :call targets#omap('-', 'last select shrink')
onoremap <silent> In- :call targets#omap('-', 'next select shrink')
onoremap <silent> I- :call targets#omap('-', 'seekselect shrink')
onoremap <silent> IL+ :call targets#omap('+', 'double last select shrink')
onoremap <silent> IN+ :call targets#omap('+', 'double next select shrink')
onoremap <silent> Il+ :call targets#omap('+', 'last select shrink')
onoremap <silent> In+ :call targets#omap('+', 'next select shrink')
onoremap <silent> I+ :call targets#omap('+', 'seekselect shrink')
onoremap <silent> IL: :call targets#omap(':', 'double last select shrink')
onoremap <silent> IN: :call targets#omap(':', 'double next select shrink')
onoremap <silent> Il: :call targets#omap(':', 'last select shrink')
onoremap <silent> In: :call targets#omap(':', 'next select shrink')
onoremap <silent> I: :call targets#omap(':', 'seekselect shrink')
onoremap <silent> IL; :call targets#omap(';', 'double last select shrink')
onoremap <silent> IN; :call targets#omap(';', 'double next select shrink')
onoremap <silent> Il; :call targets#omap(';', 'last select shrink')
onoremap <silent> In; :call targets#omap(';', 'next select shrink')
onoremap <silent> I; :call targets#omap(';', 'seekselect shrink')
onoremap <silent> IL. :call targets#omap('.', 'double last select shrink')
onoremap <silent> IN. :call targets#omap('.', 'double next select shrink')
onoremap <silent> Il. :call targets#omap('.', 'last select shrink')
onoremap <silent> In. :call targets#omap('.', 'next select shrink')
onoremap <silent> I. :call targets#omap('.', 'seekselect shrink')
onoremap <silent> IL, :call targets#omap(',', 'double last select shrink')
onoremap <silent> IN, :call targets#omap(',', 'double next select shrink')
onoremap <silent> Il, :call targets#omap(',', 'last select shrink')
onoremap <silent> In, :call targets#omap(',', 'next select shrink')
onoremap <silent> I, :call targets#omap(',', 'seekselect shrink')
onoremap <silent> IL` :call targets#omap('`', 'quote double last select shrink')
onoremap <silent> IN` :call targets#omap('`', 'quote double next select shrink')
onoremap <silent> Il` :call targets#omap('`', 'quote last select shrink')
onoremap <silent> In` :call targets#omap('`', 'quote next select shrink')
onoremap <silent> I` :call targets#omap('`', 'quote seekselect shrink')
onoremap <silent> IL' :call targets#omap('''', 'quote double last select shrink')
onoremap <silent> IN' :call targets#omap('''', 'quote double next select shrink')
onoremap <silent> Il' :call targets#omap('''', 'quote last select shrink')
onoremap <silent> In' :call targets#omap('''', 'quote next select shrink')
onoremap <silent> I' :call targets#omap('''', 'quote seekselect shrink')
onoremap <silent> IL" :call targets#omap('"', 'quote double last select shrink')
onoremap <silent> IN" :call targets#omap('"', 'quote double next select shrink')
onoremap <silent> Il" :call targets#omap('"', 'quote last select shrink')
onoremap <silent> In" :call targets#omap('"', 'quote next select shrink')
onoremap <silent> I" :call targets#omap('"', 'quote seekselect shrink')
onoremap <silent> Ilt :call targets#omap('t', 'lastt selectp innert shrink')
onoremap <silent> Int :call targets#omap('t', 'nextt selectp innert shrink')
onoremap <silent> It :call targets#omap('t', 'seekselectt innert shrink')
onoremap <silent> Il> :call targets#omap('<>', 'lastp selectp shrink')
onoremap <silent> In> :call targets#omap('<>', 'nextp selectp shrink')
onoremap <silent> I> :call targets#omap('<>', 'seekselectp shrink')
onoremap <silent> Il< :call targets#omap('<>', 'lastp selectp shrink')
onoremap <silent> In< :call targets#omap('<>', 'nextp selectp shrink')
onoremap <silent> I< :call targets#omap('<>', 'seekselectp shrink')
onoremap <silent> Il] :call targets#omap('[]', 'lastp selectp shrink')
onoremap <silent> In] :call targets#omap('[]', 'nextp selectp shrink')
onoremap <silent> I] :call targets#omap('[]', 'seekselectp shrink')
onoremap <silent> Il[ :call targets#omap('[]', 'lastp selectp shrink')
onoremap <silent> In[ :call targets#omap('[]', 'nextp selectp shrink')
onoremap <silent> I[ :call targets#omap('[]', 'seekselectp shrink')
onoremap <silent> IlB :call targets#omap('{}', 'lastp selectp shrink')
onoremap <silent> InB :call targets#omap('{}', 'nextp selectp shrink')
onoremap <silent> IB :call targets#omap('{}', 'seekselectp shrink')
onoremap <silent> Il} :call targets#omap('{}', 'lastp selectp shrink')
onoremap <silent> In} :call targets#omap('{}', 'nextp selectp shrink')
onoremap <silent> I} :call targets#omap('{}', 'seekselectp shrink')
onoremap <silent> Il{ :call targets#omap('{}', 'lastp selectp shrink')
onoremap <silent> In{ :call targets#omap('{}', 'nextp selectp shrink')
onoremap <silent> I{ :call targets#omap('{}', 'seekselectp shrink')
onoremap <silent> Ilb :call targets#omap('()', 'lastp selectp shrink')
onoremap <silent> Inb :call targets#omap('()', 'nextp selectp shrink')
onoremap <silent> Ib :call targets#omap('()', 'seekselectp shrink')
onoremap <silent> Il) :call targets#omap('()', 'lastp selectp shrink')
onoremap <silent> In) :call targets#omap('()', 'nextp selectp shrink')
onoremap <silent> I) :call targets#omap('()', 'seekselectp shrink')
onoremap <silent> Il( :call targets#omap('()', 'lastp selectp shrink')
onoremap <silent> In( :call targets#omap('()', 'nextp selectp shrink')
onoremap <silent> I( :call targets#omap('()', 'seekselectp shrink')
xmap S <Plug>VSurround
nmap \\u <Plug>CommentaryUndo:echomsg '\\ is deprecated. Use gc'
nmap \\\ <Plug>CommentaryLine:echomsg '\\ is deprecated. Use gc'
nmap \\ :echomsg '\\ is deprecated. Use gc'<Plug>Commentary
xmap \\ <Plug>Commentary:echomsg '\\ is deprecated. Use gc'
xnoremap <silent> a( :call targets#xmap('()', 'grow seekselectp')
xnoremap <silent> a) :call targets#xmap('()', 'grow seekselectp')
xnoremap <silent> ab :call targets#xmap('()', 'grow seekselectp')
xnoremap <silent> an( :call targets#xmap('()', 'nextp selectp')
xnoremap <silent> an) :call targets#xmap('()', 'nextp selectp')
xnoremap <silent> anb :call targets#xmap('()', 'nextp selectp')
xnoremap <silent> al( :call targets#xmap('()', 'lastp selectp')
xnoremap <silent> al) :call targets#xmap('()', 'lastp selectp')
xnoremap <silent> alb :call targets#xmap('()', 'lastp selectp')
xnoremap <silent> a{ :call targets#xmap('{}', 'grow seekselectp')
xnoremap <silent> a} :call targets#xmap('{}', 'grow seekselectp')
xnoremap <silent> aB :call targets#xmap('{}', 'grow seekselectp')
xnoremap <silent> an{ :call targets#xmap('{}', 'nextp selectp')
xnoremap <silent> an} :call targets#xmap('{}', 'nextp selectp')
xnoremap <silent> anB :call targets#xmap('{}', 'nextp selectp')
xnoremap <silent> al{ :call targets#xmap('{}', 'lastp selectp')
xnoremap <silent> al} :call targets#xmap('{}', 'lastp selectp')
xnoremap <silent> alB :call targets#xmap('{}', 'lastp selectp')
xnoremap <silent> a[ :call targets#xmap('[]', 'grow seekselectp')
xnoremap <silent> a] :call targets#xmap('[]', 'grow seekselectp')
onoremap <silent> ar :call targets#omap('[]', 'grow seekselectp')
xnoremap <silent> ar :call targets#xmap('[]', 'grow seekselectp')
xnoremap <silent> an[ :call targets#xmap('[]', 'nextp selectp')
xnoremap <silent> an] :call targets#xmap('[]', 'nextp selectp')
onoremap <silent> anr :call targets#omap('[]', 'nextp selectp')
xnoremap <silent> anr :call targets#xmap('[]', 'nextp selectp')
xnoremap <silent> al[ :call targets#xmap('[]', 'lastp selectp')
xnoremap <silent> al] :call targets#xmap('[]', 'lastp selectp')
onoremap <silent> alr :call targets#omap('[]', 'lastp selectp')
xnoremap <silent> alr :call targets#xmap('[]', 'lastp selectp')
xnoremap <silent> a< :call targets#xmap('<>', 'grow seekselectp')
xnoremap <silent> a> :call targets#xmap('<>', 'grow seekselectp')
xnoremap <silent> aa :call targets#xmap('<>', 'grow seekselectp')
xnoremap <silent> an< :call targets#xmap('<>', 'nextp selectp')
xnoremap <silent> an> :call targets#xmap('<>', 'nextp selectp')
xnoremap <silent> ana :call targets#xmap('<>', 'nextp selectp')
xnoremap <silent> al< :call targets#xmap('<>', 'lastp selectp')
xnoremap <silent> al> :call targets#xmap('<>', 'lastp selectp')
xnoremap <silent> ala :call targets#xmap('<>', 'lastp selectp')
xnoremap <silent> at :call targets#xmap('t', 'grow seekselectt')
xnoremap <silent> ant :call targets#xmap('t', 'nextt selectp')
xnoremap <silent> alt :call targets#xmap('t', 'lastt selectp')
xnoremap <silent> a" :call targets#xmap('"', 'quote seekselect')
xnoremap <silent> an" :call targets#xmap('"', 'quote next select')
xnoremap <silent> al" :call targets#xmap('"', 'quote last select')
xnoremap <silent> aN" :call targets#xmap('"', 'quote double next select')
xnoremap <silent> aL" :call targets#xmap('"', 'quote double last select')
xnoremap <silent> a' :call targets#xmap('''', 'quote seekselect')
xnoremap <silent> an' :call targets#xmap('''', 'quote next select')
xnoremap <silent> al' :call targets#xmap('''', 'quote last select')
xnoremap <silent> aN' :call targets#xmap('''', 'quote double next select')
xnoremap <silent> aL' :call targets#xmap('''', 'quote double last select')
xnoremap <silent> a` :call targets#xmap('`', 'quote seekselect')
xnoremap <silent> an` :call targets#xmap('`', 'quote next select')
xnoremap <silent> al` :call targets#xmap('`', 'quote last select')
xnoremap <silent> aN` :call targets#xmap('`', 'quote double next select')
xnoremap <silent> aL` :call targets#xmap('`', 'quote double last select')
xnoremap <silent> a, :call targets#xmap(',', 'seekselect dropr')
xnoremap <silent> an, :call targets#xmap(',', 'next select dropr')
xnoremap <silent> al, :call targets#xmap(',', 'last select dropr')
xnoremap <silent> aN, :call targets#xmap(',', 'double next select dropr')
xnoremap <silent> aL, :call targets#xmap(',', 'double last select dropr')
xnoremap <silent> a. :call targets#xmap('.', 'seekselect dropr')
xnoremap <silent> an. :call targets#xmap('.', 'next select dropr')
xnoremap <silent> al. :call targets#xmap('.', 'last select dropr')
xnoremap <silent> aN. :call targets#xmap('.', 'double next select dropr')
xnoremap <silent> aL. :call targets#xmap('.', 'double last select dropr')
xnoremap <silent> a; :call targets#xmap(';', 'seekselect dropr')
xnoremap <silent> an; :call targets#xmap(';', 'next select dropr')
xnoremap <silent> al; :call targets#xmap(';', 'last select dropr')
xnoremap <silent> aN; :call targets#xmap(';', 'double next select dropr')
xnoremap <silent> aL; :call targets#xmap(';', 'double last select dropr')
xnoremap <silent> a: :call targets#xmap(':', 'seekselect dropr')
xnoremap <silent> an: :call targets#xmap(':', 'next select dropr')
xnoremap <silent> al: :call targets#xmap(':', 'last select dropr')
xnoremap <silent> aN: :call targets#xmap(':', 'double next select dropr')
xnoremap <silent> aL: :call targets#xmap(':', 'double last select dropr')
xnoremap <silent> a+ :call targets#xmap('+', 'seekselect dropr')
xnoremap <silent> an+ :call targets#xmap('+', 'next select dropr')
xnoremap <silent> al+ :call targets#xmap('+', 'last select dropr')
xnoremap <silent> aN+ :call targets#xmap('+', 'double next select dropr')
xnoremap <silent> aL+ :call targets#xmap('+', 'double last select dropr')
xnoremap <silent> a- :call targets#xmap('-', 'seekselect dropr')
xnoremap <silent> an- :call targets#xmap('-', 'next select dropr')
xnoremap <silent> al- :call targets#xmap('-', 'last select dropr')
xnoremap <silent> aN- :call targets#xmap('-', 'double next select dropr')
xnoremap <silent> aL- :call targets#xmap('-', 'double last select dropr')
xnoremap <silent> a= :call targets#xmap('=', 'seekselect dropr')
xnoremap <silent> an= :call targets#xmap('=', 'next select dropr')
xnoremap <silent> al= :call targets#xmap('=', 'last select dropr')
xnoremap <silent> aN= :call targets#xmap('=', 'double next select dropr')
xnoremap <silent> aL= :call targets#xmap('=', 'double last select dropr')
xnoremap <silent> a~ :call targets#xmap('~', 'seekselect dropr')
xnoremap <silent> an~ :call targets#xmap('~', 'next select dropr')
xnoremap <silent> al~ :call targets#xmap('~', 'last select dropr')
xnoremap <silent> aN~ :call targets#xmap('~', 'double next select dropr')
xnoremap <silent> aL~ :call targets#xmap('~', 'double last select dropr')
xnoremap <silent> a_ :call targets#xmap('_', 'seekselect dropr')
xnoremap <silent> an_ :call targets#xmap('_', 'next select dropr')
xnoremap <silent> al_ :call targets#xmap('_', 'last select dropr')
xnoremap <silent> aN_ :call targets#xmap('_', 'double next select dropr')
xnoremap <silent> aL_ :call targets#xmap('_', 'double last select dropr')
xnoremap <silent> a* :call targets#xmap('*', 'seekselect dropr')
xnoremap <silent> an* :call targets#xmap('*', 'next select dropr')
xnoremap <silent> al* :call targets#xmap('*', 'last select dropr')
xnoremap <silent> aN* :call targets#xmap('*', 'double next select dropr')
xnoremap <silent> aL* :call targets#xmap('*', 'double last select dropr')
xnoremap <silent> a# :call targets#xmap('#', 'seekselect dropr')
xnoremap <silent> an# :call targets#xmap('#', 'next select dropr')
xnoremap <silent> al# :call targets#xmap('#', 'last select dropr')
xnoremap <silent> aN# :call targets#xmap('#', 'double next select dropr')
xnoremap <silent> aL# :call targets#xmap('#', 'double last select dropr')
xnoremap <silent> a/ :call targets#xmap('/', 'seekselect dropr')
xnoremap <silent> an/ :call targets#xmap('/', 'next select dropr')
xnoremap <silent> al/ :call targets#xmap('/', 'last select dropr')
xnoremap <silent> aN/ :call targets#xmap('/', 'double next select dropr')
xnoremap <silent> aL/ :call targets#xmap('/', 'double last select dropr')
xnoremap <silent> a\ :call targets#xmap('\', 'seekselect dropr')
xnoremap <silent> an\ :call targets#xmap('\', 'next select dropr')
xnoremap <silent> al\ :call targets#xmap('\', 'last select dropr')
xnoremap <silent> aN\ :call targets#xmap('\', 'double next select dropr')
xnoremap <silent> aL\ :call targets#xmap('\', 'double last select dropr')
xnoremap <silent> a| :call targets#xmap('|', 'seekselect dropr')
xnoremap <silent> an| :call targets#xmap('|', 'next select dropr')
xnoremap <silent> al| :call targets#xmap('|', 'last select dropr')
xnoremap <silent> aN| :call targets#xmap('|', 'double next select dropr')
xnoremap <silent> aL| :call targets#xmap('|', 'double last select dropr')
xnoremap <silent> a& :call targets#xmap('&', 'seekselect dropr')
xnoremap <silent> an& :call targets#xmap('&', 'next select dropr')
xnoremap <silent> al& :call targets#xmap('&', 'last select dropr')
xnoremap <silent> aN& :call targets#xmap('&', 'double next select dropr')
xnoremap <silent> aL& :call targets#xmap('&', 'double last select dropr')
xnoremap <silent> a$ :call targets#xmap('$', 'seekselect dropr')
xnoremap <silent> an$ :call targets#xmap('$', 'next select dropr')
xnoremap <silent> al$ :call targets#xmap('$', 'last select dropr')
xnoremap <silent> aN$ :call targets#xmap('$', 'double next select dropr')
xnoremap <silent> aL$ :call targets#xmap('$', 'double last select dropr')
xnoremap <silent> <expr> a targets#e('a')
onoremap <silent> ala :call targets#omap('<>', 'lastp selectp')
onoremap <silent> ana :call targets#omap('<>', 'nextp selectp')
onoremap <silent> aa :call targets#omap('<>', 'grow seekselectp')
onoremap <silent> aL$ :call targets#omap('$', 'double last select dropr')
onoremap <silent> aN$ :call targets#omap('$', 'double next select dropr')
onoremap <silent> al$ :call targets#omap('$', 'last select dropr')
onoremap <silent> an$ :call targets#omap('$', 'next select dropr')
onoremap <silent> a$ :call targets#omap('$', 'seekselect dropr')
onoremap <silent> aL& :call targets#omap('&', 'double last select dropr')
onoremap <silent> aN& :call targets#omap('&', 'double next select dropr')
onoremap <silent> al& :call targets#omap('&', 'last select dropr')
onoremap <silent> an& :call targets#omap('&', 'next select dropr')
onoremap <silent> a& :call targets#omap('&', 'seekselect dropr')
onoremap <silent> aL| :call targets#omap('|', 'double last select dropr')
onoremap <silent> aN| :call targets#omap('|', 'double next select dropr')
onoremap <silent> al| :call targets#omap('|', 'last select dropr')
onoremap <silent> an| :call targets#omap('|', 'next select dropr')
onoremap <silent> a| :call targets#omap('|', 'seekselect dropr')
onoremap <silent> aL\ :call targets#omap('\', 'double last select dropr')
onoremap <silent> aN\ :call targets#omap('\', 'double next select dropr')
onoremap <silent> al\ :call targets#omap('\', 'last select dropr')
onoremap <silent> an\ :call targets#omap('\', 'next select dropr')
onoremap <silent> a\ :call targets#omap('\', 'seekselect dropr')
onoremap <silent> aL/ :call targets#omap('/', 'double last select dropr')
onoremap <silent> aN/ :call targets#omap('/', 'double next select dropr')
onoremap <silent> al/ :call targets#omap('/', 'last select dropr')
onoremap <silent> an/ :call targets#omap('/', 'next select dropr')
onoremap <silent> a/ :call targets#omap('/', 'seekselect dropr')
onoremap <silent> aL# :call targets#omap('#', 'double last select dropr')
onoremap <silent> aN# :call targets#omap('#', 'double next select dropr')
onoremap <silent> al# :call targets#omap('#', 'last select dropr')
onoremap <silent> an# :call targets#omap('#', 'next select dropr')
onoremap <silent> a# :call targets#omap('#', 'seekselect dropr')
onoremap <silent> aL* :call targets#omap('*', 'double last select dropr')
onoremap <silent> aN* :call targets#omap('*', 'double next select dropr')
onoremap <silent> al* :call targets#omap('*', 'last select dropr')
onoremap <silent> an* :call targets#omap('*', 'next select dropr')
onoremap <silent> a* :call targets#omap('*', 'seekselect dropr')
onoremap <silent> aL_ :call targets#omap('_', 'double last select dropr')
onoremap <silent> aN_ :call targets#omap('_', 'double next select dropr')
onoremap <silent> al_ :call targets#omap('_', 'last select dropr')
onoremap <silent> an_ :call targets#omap('_', 'next select dropr')
onoremap <silent> a_ :call targets#omap('_', 'seekselect dropr')
onoremap <silent> aL~ :call targets#omap('~', 'double last select dropr')
onoremap <silent> aN~ :call targets#omap('~', 'double next select dropr')
onoremap <silent> al~ :call targets#omap('~', 'last select dropr')
onoremap <silent> an~ :call targets#omap('~', 'next select dropr')
onoremap <silent> a~ :call targets#omap('~', 'seekselect dropr')
onoremap <silent> aL= :call targets#omap('=', 'double last select dropr')
onoremap <silent> aN= :call targets#omap('=', 'double next select dropr')
onoremap <silent> al= :call targets#omap('=', 'last select dropr')
onoremap <silent> an= :call targets#omap('=', 'next select dropr')
onoremap <silent> a= :call targets#omap('=', 'seekselect dropr')
onoremap <silent> aL- :call targets#omap('-', 'double last select dropr')
onoremap <silent> aN- :call targets#omap('-', 'double next select dropr')
onoremap <silent> al- :call targets#omap('-', 'last select dropr')
onoremap <silent> an- :call targets#omap('-', 'next select dropr')
onoremap <silent> a- :call targets#omap('-', 'seekselect dropr')
onoremap <silent> aL+ :call targets#omap('+', 'double last select dropr')
onoremap <silent> aN+ :call targets#omap('+', 'double next select dropr')
onoremap <silent> al+ :call targets#omap('+', 'last select dropr')
onoremap <silent> an+ :call targets#omap('+', 'next select dropr')
onoremap <silent> a+ :call targets#omap('+', 'seekselect dropr')
onoremap <silent> aL: :call targets#omap(':', 'double last select dropr')
onoremap <silent> aN: :call targets#omap(':', 'double next select dropr')
onoremap <silent> al: :call targets#omap(':', 'last select dropr')
onoremap <silent> an: :call targets#omap(':', 'next select dropr')
onoremap <silent> a: :call targets#omap(':', 'seekselect dropr')
onoremap <silent> aL; :call targets#omap(';', 'double last select dropr')
onoremap <silent> aN; :call targets#omap(';', 'double next select dropr')
onoremap <silent> al; :call targets#omap(';', 'last select dropr')
onoremap <silent> an; :call targets#omap(';', 'next select dropr')
onoremap <silent> a; :call targets#omap(';', 'seekselect dropr')
onoremap <silent> aL. :call targets#omap('.', 'double last select dropr')
onoremap <silent> aN. :call targets#omap('.', 'double next select dropr')
onoremap <silent> al. :call targets#omap('.', 'last select dropr')
onoremap <silent> an. :call targets#omap('.', 'next select dropr')
onoremap <silent> a. :call targets#omap('.', 'seekselect dropr')
onoremap <silent> aL, :call targets#omap(',', 'double last select dropr')
onoremap <silent> aN, :call targets#omap(',', 'double next select dropr')
onoremap <silent> al, :call targets#omap(',', 'last select dropr')
onoremap <silent> an, :call targets#omap(',', 'next select dropr')
onoremap <silent> a, :call targets#omap(',', 'seekselect dropr')
onoremap <silent> aL` :call targets#omap('`', 'quote double last select')
onoremap <silent> aN` :call targets#omap('`', 'quote double next select')
onoremap <silent> al` :call targets#omap('`', 'quote last select')
onoremap <silent> an` :call targets#omap('`', 'quote next select')
onoremap <silent> a` :call targets#omap('`', 'quote seekselect')
onoremap <silent> aL' :call targets#omap('''', 'quote double last select')
onoremap <silent> aN' :call targets#omap('''', 'quote double next select')
onoremap <silent> al' :call targets#omap('''', 'quote last select')
onoremap <silent> an' :call targets#omap('''', 'quote next select')
onoremap <silent> a' :call targets#omap('''', 'quote seekselect')
onoremap <silent> aL" :call targets#omap('"', 'quote double last select')
onoremap <silent> aN" :call targets#omap('"', 'quote double next select')
onoremap <silent> al" :call targets#omap('"', 'quote last select')
onoremap <silent> an" :call targets#omap('"', 'quote next select')
onoremap <silent> a" :call targets#omap('"', 'quote seekselect')
onoremap <silent> alt :call targets#omap('t', 'lastt selectp')
onoremap <silent> ant :call targets#omap('t', 'nextt selectp')
onoremap <silent> at :call targets#omap('t', 'grow seekselectt')
onoremap <silent> al> :call targets#omap('<>', 'lastp selectp')
onoremap <silent> an> :call targets#omap('<>', 'nextp selectp')
onoremap <silent> a> :call targets#omap('<>', 'grow seekselectp')
onoremap <silent> al< :call targets#omap('<>', 'lastp selectp')
onoremap <silent> an< :call targets#omap('<>', 'nextp selectp')
onoremap <silent> a< :call targets#omap('<>', 'grow seekselectp')
onoremap <silent> al] :call targets#omap('[]', 'lastp selectp')
onoremap <silent> an] :call targets#omap('[]', 'nextp selectp')
onoremap <silent> a] :call targets#omap('[]', 'grow seekselectp')
onoremap <silent> al[ :call targets#omap('[]', 'lastp selectp')
onoremap <silent> an[ :call targets#omap('[]', 'nextp selectp')
onoremap <silent> a[ :call targets#omap('[]', 'grow seekselectp')
onoremap <silent> alB :call targets#omap('{}', 'lastp selectp')
onoremap <silent> anB :call targets#omap('{}', 'nextp selectp')
onoremap <silent> aB :call targets#omap('{}', 'grow seekselectp')
onoremap <silent> al} :call targets#omap('{}', 'lastp selectp')
onoremap <silent> an} :call targets#omap('{}', 'nextp selectp')
onoremap <silent> a} :call targets#omap('{}', 'grow seekselectp')
onoremap <silent> al{ :call targets#omap('{}', 'lastp selectp')
onoremap <silent> an{ :call targets#omap('{}', 'nextp selectp')
onoremap <silent> a{ :call targets#omap('{}', 'grow seekselectp')
onoremap <silent> alb :call targets#omap('()', 'lastp selectp')
onoremap <silent> anb :call targets#omap('()', 'nextp selectp')
onoremap <silent> ab :call targets#omap('()', 'grow seekselectp')
onoremap <silent> al) :call targets#omap('()', 'lastp selectp')
onoremap <silent> an) :call targets#omap('()', 'nextp selectp')
onoremap <silent> a) :call targets#omap('()', 'grow seekselectp')
onoremap <silent> al( :call targets#omap('()', 'lastp selectp')
onoremap <silent> an( :call targets#omap('()', 'nextp selectp')
onoremap <silent> a( :call targets#omap('()', 'grow seekselectp')
nmap cgc <Plug>ChangeCommentary
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nmap ds <Plug>Dsurround
nmap gx <Plug>NetrwBrowseX
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
xmap gS <Plug>VgSurround
nnoremap gj j
nnoremap gk k
xnoremap <silent> i( :call targets#xmap('()', 'grow seekselectp drop')
xnoremap <silent> i) :call targets#xmap('()', 'grow seekselectp drop')
xnoremap <silent> ib :call targets#xmap('()', 'grow seekselectp drop')
xnoremap <silent> in( :call targets#xmap('()', 'nextp selectp drop')
xnoremap <silent> in) :call targets#xmap('()', 'nextp selectp drop')
xnoremap <silent> inb :call targets#xmap('()', 'nextp selectp drop')
xnoremap <silent> il( :call targets#xmap('()', 'lastp selectp drop')
xnoremap <silent> il) :call targets#xmap('()', 'lastp selectp drop')
xnoremap <silent> ilb :call targets#xmap('()', 'lastp selectp drop')
xnoremap <silent> i{ :call targets#xmap('{}', 'grow seekselectp drop')
xnoremap <silent> i} :call targets#xmap('{}', 'grow seekselectp drop')
xnoremap <silent> iB :call targets#xmap('{}', 'grow seekselectp drop')
xnoremap <silent> in{ :call targets#xmap('{}', 'nextp selectp drop')
xnoremap <silent> in} :call targets#xmap('{}', 'nextp selectp drop')
xnoremap <silent> inB :call targets#xmap('{}', 'nextp selectp drop')
xnoremap <silent> il{ :call targets#xmap('{}', 'lastp selectp drop')
xnoremap <silent> il} :call targets#xmap('{}', 'lastp selectp drop')
xnoremap <silent> ilB :call targets#xmap('{}', 'lastp selectp drop')
xnoremap <silent> i[ :call targets#xmap('[]', 'grow seekselectp drop')
xnoremap <silent> i] :call targets#xmap('[]', 'grow seekselectp drop')
onoremap <silent> ir :call targets#omap('[]', 'grow seekselectp drop')
xnoremap <silent> ir :call targets#xmap('[]', 'grow seekselectp drop')
xnoremap <silent> in[ :call targets#xmap('[]', 'nextp selectp drop')
xnoremap <silent> in] :call targets#xmap('[]', 'nextp selectp drop')
onoremap <silent> inr :call targets#omap('[]', 'nextp selectp drop')
xnoremap <silent> inr :call targets#xmap('[]', 'nextp selectp drop')
xnoremap <silent> il[ :call targets#xmap('[]', 'lastp selectp drop')
xnoremap <silent> il] :call targets#xmap('[]', 'lastp selectp drop')
onoremap <silent> ilr :call targets#omap('[]', 'lastp selectp drop')
xnoremap <silent> ilr :call targets#xmap('[]', 'lastp selectp drop')
xnoremap <silent> i< :call targets#xmap('<>', 'grow seekselectp drop')
xnoremap <silent> i> :call targets#xmap('<>', 'grow seekselectp drop')
xnoremap <silent> ia :call targets#xmap('<>', 'grow seekselectp drop')
xnoremap <silent> in< :call targets#xmap('<>', 'nextp selectp drop')
xnoremap <silent> in> :call targets#xmap('<>', 'nextp selectp drop')
xnoremap <silent> ina :call targets#xmap('<>', 'nextp selectp drop')
xnoremap <silent> il< :call targets#xmap('<>', 'lastp selectp drop')
xnoremap <silent> il> :call targets#xmap('<>', 'lastp selectp drop')
xnoremap <silent> ila :call targets#xmap('<>', 'lastp selectp drop')
xnoremap <silent> it :call targets#xmap('t', 'grow seekselectt innert drop')
xnoremap <silent> int :call targets#xmap('t', 'nextt selectp innert drop')
xnoremap <silent> ilt :call targets#xmap('t', 'lastt selectp innert drop')
xnoremap <silent> i" :call targets#xmap('"', 'quote seekselect drop')
xnoremap <silent> in" :call targets#xmap('"', 'quote next select drop')
xnoremap <silent> il" :call targets#xmap('"', 'quote last select drop')
xnoremap <silent> iN" :call targets#xmap('"', 'quote double next select drop')
xnoremap <silent> iL" :call targets#xmap('"', 'quote double last select drop')
xnoremap <silent> i' :call targets#xmap('''', 'quote seekselect drop')
xnoremap <silent> in' :call targets#xmap('''', 'quote next select drop')
xnoremap <silent> il' :call targets#xmap('''', 'quote last select drop')
xnoremap <silent> iN' :call targets#xmap('''', 'quote double next select drop')
xnoremap <silent> iL' :call targets#xmap('''', 'quote double last select drop')
xnoremap <silent> i` :call targets#xmap('`', 'quote seekselect drop')
xnoremap <silent> in` :call targets#xmap('`', 'quote next select drop')
xnoremap <silent> il` :call targets#xmap('`', 'quote last select drop')
xnoremap <silent> iN` :call targets#xmap('`', 'quote double next select drop')
xnoremap <silent> iL` :call targets#xmap('`', 'quote double last select drop')
xnoremap <silent> i, :call targets#xmap(',', 'seekselect drop')
xnoremap <silent> in, :call targets#xmap(',', 'next select drop')
xnoremap <silent> il, :call targets#xmap(',', 'last select drop')
xnoremap <silent> iN, :call targets#xmap(',', 'double next select drop')
xnoremap <silent> iL, :call targets#xmap(',', 'double last select drop')
xnoremap <silent> i. :call targets#xmap('.', 'seekselect drop')
xnoremap <silent> in. :call targets#xmap('.', 'next select drop')
xnoremap <silent> il. :call targets#xmap('.', 'last select drop')
xnoremap <silent> iN. :call targets#xmap('.', 'double next select drop')
xnoremap <silent> iL. :call targets#xmap('.', 'double last select drop')
xnoremap <silent> i; :call targets#xmap(';', 'seekselect drop')
xnoremap <silent> in; :call targets#xmap(';', 'next select drop')
xnoremap <silent> il; :call targets#xmap(';', 'last select drop')
xnoremap <silent> iN; :call targets#xmap(';', 'double next select drop')
xnoremap <silent> iL; :call targets#xmap(';', 'double last select drop')
xnoremap <silent> i: :call targets#xmap(':', 'seekselect drop')
xnoremap <silent> in: :call targets#xmap(':', 'next select drop')
xnoremap <silent> il: :call targets#xmap(':', 'last select drop')
xnoremap <silent> iN: :call targets#xmap(':', 'double next select drop')
xnoremap <silent> iL: :call targets#xmap(':', 'double last select drop')
xnoremap <silent> i+ :call targets#xmap('+', 'seekselect drop')
xnoremap <silent> in+ :call targets#xmap('+', 'next select drop')
xnoremap <silent> il+ :call targets#xmap('+', 'last select drop')
xnoremap <silent> iN+ :call targets#xmap('+', 'double next select drop')
xnoremap <silent> iL+ :call targets#xmap('+', 'double last select drop')
xnoremap <silent> i- :call targets#xmap('-', 'seekselect drop')
xnoremap <silent> in- :call targets#xmap('-', 'next select drop')
xnoremap <silent> il- :call targets#xmap('-', 'last select drop')
xnoremap <silent> iN- :call targets#xmap('-', 'double next select drop')
xnoremap <silent> iL- :call targets#xmap('-', 'double last select drop')
xnoremap <silent> i= :call targets#xmap('=', 'seekselect drop')
xnoremap <silent> in= :call targets#xmap('=', 'next select drop')
xnoremap <silent> il= :call targets#xmap('=', 'last select drop')
xnoremap <silent> iN= :call targets#xmap('=', 'double next select drop')
xnoremap <silent> iL= :call targets#xmap('=', 'double last select drop')
xnoremap <silent> i~ :call targets#xmap('~', 'seekselect drop')
xnoremap <silent> in~ :call targets#xmap('~', 'next select drop')
xnoremap <silent> il~ :call targets#xmap('~', 'last select drop')
xnoremap <silent> iN~ :call targets#xmap('~', 'double next select drop')
xnoremap <silent> iL~ :call targets#xmap('~', 'double last select drop')
xnoremap <silent> i_ :call targets#xmap('_', 'seekselect drop')
xnoremap <silent> in_ :call targets#xmap('_', 'next select drop')
xnoremap <silent> il_ :call targets#xmap('_', 'last select drop')
xnoremap <silent> iN_ :call targets#xmap('_', 'double next select drop')
xnoremap <silent> iL_ :call targets#xmap('_', 'double last select drop')
xnoremap <silent> i* :call targets#xmap('*', 'seekselect drop')
xnoremap <silent> in* :call targets#xmap('*', 'next select drop')
xnoremap <silent> il* :call targets#xmap('*', 'last select drop')
xnoremap <silent> iN* :call targets#xmap('*', 'double next select drop')
xnoremap <silent> iL* :call targets#xmap('*', 'double last select drop')
xnoremap <silent> i# :call targets#xmap('#', 'seekselect drop')
xnoremap <silent> in# :call targets#xmap('#', 'next select drop')
xnoremap <silent> il# :call targets#xmap('#', 'last select drop')
xnoremap <silent> iN# :call targets#xmap('#', 'double next select drop')
xnoremap <silent> iL# :call targets#xmap('#', 'double last select drop')
xnoremap <silent> i/ :call targets#xmap('/', 'seekselect drop')
xnoremap <silent> in/ :call targets#xmap('/', 'next select drop')
xnoremap <silent> il/ :call targets#xmap('/', 'last select drop')
xnoremap <silent> iN/ :call targets#xmap('/', 'double next select drop')
xnoremap <silent> iL/ :call targets#xmap('/', 'double last select drop')
xnoremap <silent> i\ :call targets#xmap('\', 'seekselect drop')
xnoremap <silent> in\ :call targets#xmap('\', 'next select drop')
xnoremap <silent> il\ :call targets#xmap('\', 'last select drop')
xnoremap <silent> iN\ :call targets#xmap('\', 'double next select drop')
xnoremap <silent> iL\ :call targets#xmap('\', 'double last select drop')
xnoremap <silent> i| :call targets#xmap('|', 'seekselect drop')
xnoremap <silent> in| :call targets#xmap('|', 'next select drop')
xnoremap <silent> il| :call targets#xmap('|', 'last select drop')
xnoremap <silent> iN| :call targets#xmap('|', 'double next select drop')
xnoremap <silent> iL| :call targets#xmap('|', 'double last select drop')
xnoremap <silent> i& :call targets#xmap('&', 'seekselect drop')
xnoremap <silent> in& :call targets#xmap('&', 'next select drop')
xnoremap <silent> il& :call targets#xmap('&', 'last select drop')
xnoremap <silent> iN& :call targets#xmap('&', 'double next select drop')
xnoremap <silent> iL& :call targets#xmap('&', 'double last select drop')
xnoremap <silent> i$ :call targets#xmap('$', 'seekselect drop')
xnoremap <silent> in$ :call targets#xmap('$', 'next select drop')
xnoremap <silent> il$ :call targets#xmap('$', 'last select drop')
xnoremap <silent> iN$ :call targets#xmap('$', 'double next select drop')
xnoremap <silent> iL$ :call targets#xmap('$', 'double last select drop')
xnoremap <silent> <expr> i targets#e('i')
onoremap <silent> ila :call targets#omap('<>', 'lastp selectp drop')
onoremap <silent> ina :call targets#omap('<>', 'nextp selectp drop')
onoremap <silent> ia :call targets#omap('<>', 'grow seekselectp drop')
onoremap <silent> iL$ :call targets#omap('$', 'double last select drop')
onoremap <silent> iN$ :call targets#omap('$', 'double next select drop')
onoremap <silent> il$ :call targets#omap('$', 'last select drop')
onoremap <silent> in$ :call targets#omap('$', 'next select drop')
onoremap <silent> i$ :call targets#omap('$', 'seekselect drop')
onoremap <silent> iL& :call targets#omap('&', 'double last select drop')
onoremap <silent> iN& :call targets#omap('&', 'double next select drop')
onoremap <silent> il& :call targets#omap('&', 'last select drop')
onoremap <silent> in& :call targets#omap('&', 'next select drop')
onoremap <silent> i& :call targets#omap('&', 'seekselect drop')
onoremap <silent> iL| :call targets#omap('|', 'double last select drop')
onoremap <silent> iN| :call targets#omap('|', 'double next select drop')
onoremap <silent> il| :call targets#omap('|', 'last select drop')
onoremap <silent> in| :call targets#omap('|', 'next select drop')
onoremap <silent> i| :call targets#omap('|', 'seekselect drop')
onoremap <silent> iL\ :call targets#omap('\', 'double last select drop')
onoremap <silent> iN\ :call targets#omap('\', 'double next select drop')
onoremap <silent> il\ :call targets#omap('\', 'last select drop')
onoremap <silent> in\ :call targets#omap('\', 'next select drop')
onoremap <silent> i\ :call targets#omap('\', 'seekselect drop')
onoremap <silent> iL/ :call targets#omap('/', 'double last select drop')
onoremap <silent> iN/ :call targets#omap('/', 'double next select drop')
onoremap <silent> il/ :call targets#omap('/', 'last select drop')
onoremap <silent> in/ :call targets#omap('/', 'next select drop')
onoremap <silent> i/ :call targets#omap('/', 'seekselect drop')
onoremap <silent> iL# :call targets#omap('#', 'double last select drop')
onoremap <silent> iN# :call targets#omap('#', 'double next select drop')
onoremap <silent> il# :call targets#omap('#', 'last select drop')
onoremap <silent> in# :call targets#omap('#', 'next select drop')
onoremap <silent> i# :call targets#omap('#', 'seekselect drop')
onoremap <silent> iL* :call targets#omap('*', 'double last select drop')
onoremap <silent> iN* :call targets#omap('*', 'double next select drop')
onoremap <silent> il* :call targets#omap('*', 'last select drop')
onoremap <silent> in* :call targets#omap('*', 'next select drop')
onoremap <silent> i* :call targets#omap('*', 'seekselect drop')
onoremap <silent> iL_ :call targets#omap('_', 'double last select drop')
onoremap <silent> iN_ :call targets#omap('_', 'double next select drop')
onoremap <silent> il_ :call targets#omap('_', 'last select drop')
onoremap <silent> in_ :call targets#omap('_', 'next select drop')
onoremap <silent> i_ :call targets#omap('_', 'seekselect drop')
onoremap <silent> iL~ :call targets#omap('~', 'double last select drop')
onoremap <silent> iN~ :call targets#omap('~', 'double next select drop')
onoremap <silent> il~ :call targets#omap('~', 'last select drop')
onoremap <silent> in~ :call targets#omap('~', 'next select drop')
onoremap <silent> i~ :call targets#omap('~', 'seekselect drop')
onoremap <silent> iL= :call targets#omap('=', 'double last select drop')
onoremap <silent> iN= :call targets#omap('=', 'double next select drop')
onoremap <silent> il= :call targets#omap('=', 'last select drop')
onoremap <silent> in= :call targets#omap('=', 'next select drop')
onoremap <silent> i= :call targets#omap('=', 'seekselect drop')
onoremap <silent> iL- :call targets#omap('-', 'double last select drop')
onoremap <silent> iN- :call targets#omap('-', 'double next select drop')
onoremap <silent> il- :call targets#omap('-', 'last select drop')
onoremap <silent> in- :call targets#omap('-', 'next select drop')
onoremap <silent> i- :call targets#omap('-', 'seekselect drop')
onoremap <silent> iL+ :call targets#omap('+', 'double last select drop')
onoremap <silent> iN+ :call targets#omap('+', 'double next select drop')
onoremap <silent> il+ :call targets#omap('+', 'last select drop')
onoremap <silent> in+ :call targets#omap('+', 'next select drop')
onoremap <silent> i+ :call targets#omap('+', 'seekselect drop')
onoremap <silent> iL: :call targets#omap(':', 'double last select drop')
onoremap <silent> iN: :call targets#omap(':', 'double next select drop')
onoremap <silent> il: :call targets#omap(':', 'last select drop')
onoremap <silent> in: :call targets#omap(':', 'next select drop')
onoremap <silent> i: :call targets#omap(':', 'seekselect drop')
onoremap <silent> iL; :call targets#omap(';', 'double last select drop')
onoremap <silent> iN; :call targets#omap(';', 'double next select drop')
onoremap <silent> il; :call targets#omap(';', 'last select drop')
onoremap <silent> in; :call targets#omap(';', 'next select drop')
onoremap <silent> i; :call targets#omap(';', 'seekselect drop')
onoremap <silent> iL. :call targets#omap('.', 'double last select drop')
onoremap <silent> iN. :call targets#omap('.', 'double next select drop')
onoremap <silent> il. :call targets#omap('.', 'last select drop')
onoremap <silent> in. :call targets#omap('.', 'next select drop')
onoremap <silent> i. :call targets#omap('.', 'seekselect drop')
onoremap <silent> iL, :call targets#omap(',', 'double last select drop')
onoremap <silent> iN, :call targets#omap(',', 'double next select drop')
onoremap <silent> il, :call targets#omap(',', 'last select drop')
onoremap <silent> in, :call targets#omap(',', 'next select drop')
onoremap <silent> i, :call targets#omap(',', 'seekselect drop')
onoremap <silent> iL` :call targets#omap('`', 'quote double last select drop')
onoremap <silent> iN` :call targets#omap('`', 'quote double next select drop')
onoremap <silent> il` :call targets#omap('`', 'quote last select drop')
onoremap <silent> in` :call targets#omap('`', 'quote next select drop')
onoremap <silent> i` :call targets#omap('`', 'quote seekselect drop')
onoremap <silent> iL' :call targets#omap('''', 'quote double last select drop')
onoremap <silent> iN' :call targets#omap('''', 'quote double next select drop')
onoremap <silent> il' :call targets#omap('''', 'quote last select drop')
onoremap <silent> in' :call targets#omap('''', 'quote next select drop')
onoremap <silent> i' :call targets#omap('''', 'quote seekselect drop')
onoremap <silent> iL" :call targets#omap('"', 'quote double last select drop')
onoremap <silent> iN" :call targets#omap('"', 'quote double next select drop')
onoremap <silent> il" :call targets#omap('"', 'quote last select drop')
onoremap <silent> in" :call targets#omap('"', 'quote next select drop')
onoremap <silent> i" :call targets#omap('"', 'quote seekselect drop')
onoremap <silent> ilt :call targets#omap('t', 'lastt selectp innert drop')
onoremap <silent> int :call targets#omap('t', 'nextt selectp innert drop')
onoremap <silent> it :call targets#omap('t', 'grow seekselectt innert drop')
onoremap <silent> il> :call targets#omap('<>', 'lastp selectp drop')
onoremap <silent> in> :call targets#omap('<>', 'nextp selectp drop')
onoremap <silent> i> :call targets#omap('<>', 'grow seekselectp drop')
onoremap <silent> il< :call targets#omap('<>', 'lastp selectp drop')
onoremap <silent> in< :call targets#omap('<>', 'nextp selectp drop')
onoremap <silent> i< :call targets#omap('<>', 'grow seekselectp drop')
onoremap <silent> il] :call targets#omap('[]', 'lastp selectp drop')
onoremap <silent> in] :call targets#omap('[]', 'nextp selectp drop')
onoremap <silent> i] :call targets#omap('[]', 'grow seekselectp drop')
onoremap <silent> il[ :call targets#omap('[]', 'lastp selectp drop')
onoremap <silent> in[ :call targets#omap('[]', 'nextp selectp drop')
onoremap <silent> i[ :call targets#omap('[]', 'grow seekselectp drop')
onoremap <silent> ilB :call targets#omap('{}', 'lastp selectp drop')
onoremap <silent> inB :call targets#omap('{}', 'nextp selectp drop')
onoremap <silent> iB :call targets#omap('{}', 'grow seekselectp drop')
onoremap <silent> il} :call targets#omap('{}', 'lastp selectp drop')
onoremap <silent> in} :call targets#omap('{}', 'nextp selectp drop')
onoremap <silent> i} :call targets#omap('{}', 'grow seekselectp drop')
onoremap <silent> il{ :call targets#omap('{}', 'lastp selectp drop')
onoremap <silent> in{ :call targets#omap('{}', 'nextp selectp drop')
onoremap <silent> i{ :call targets#omap('{}', 'grow seekselectp drop')
onoremap <silent> ilb :call targets#omap('()', 'lastp selectp drop')
onoremap <silent> inb :call targets#omap('()', 'nextp selectp drop')
onoremap <silent> ib :call targets#omap('()', 'grow seekselectp drop')
onoremap <silent> il) :call targets#omap('()', 'lastp selectp drop')
onoremap <silent> in) :call targets#omap('()', 'nextp selectp drop')
onoremap <silent> i) :call targets#omap('()', 'grow seekselectp drop')
onoremap <silent> il( :call targets#omap('()', 'lastp selectp drop')
onoremap <silent> in( :call targets#omap('()', 'nextp selectp drop')
onoremap <silent> i( :call targets#omap('()', 'grow seekselectp drop')
nnoremap j gj
nnoremap k gk
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cWORD>"),0)
nmap <silent> <Plug>CommentaryUndo <Plug>Commentary<Plug>Commentary
nnoremap <silent> <Plug>SurroundRepeat .
snoremap <silent> <Del> c
snoremap <silent> <BS> c
snoremap <silent> <C-Tab> :call UltiSnips#ListSnippets()
xmap <BS> "-d
vmap <D-x> "*d
vmap <D-c> "*y
vmap <D-v> "-d"*P
nmap <D-v> "*P
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap <silent> 	 =UltiSnips#ExpandSnippetOrJump()
imap  <Plug>Isurround
cabbr rename =getcmdpos() == 1 && getcmdtype() == ":" ? "Rename" : "rename"
cnoreabbr <expr> help getcmdtype() == ":" && getcmdline() == "help" ? "vertical help" : "help"
cnoreabbr <expr> h getcmdtype() == ":" && getcmdline() == "h" ? "vertical h" : "h"
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set backspace=indent,eol,start
set completeopt=menuone
set fileencodings=ucs-bom,utf-8,default,latin1
set formatoptions=tcqor2
set helplang=en
set hidden
set incsearch
set pumheight=20
set ruler
set runtimepath=~/.vim,~/.vim/bundle/vundle,~/.vim/bundle/tabular,~/.vim/bundle/smartfile,~/.vim/bundle/rename.vim,~/.vim/bundle/vim-colorschemes,~/.vim/bundle/vim-colors-solarized,~/.vim/bundle/clang_complete,~/.vim/bundle/supertab,~/.vim/bundle/ultisnips,~/.vim/bundle/vim-snippets,~/.vim/bundle/vim-markdown,~/.vim/bundle/vim-surround,~/.vim/bundle/targets.vim,~/.vim/bundle/vim-repeat,~/.vim/bundle/vim-commentary,/opt/local/share/vim/vimfiles,/opt/local/share/vim/vim74,/opt/local/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/vundle/after,~/.vim/bundle/tabular/after,~/.vim/bundle/smartfile/after,~/.vim/bundle/rename.vim/after,~/.vim/bundle/vim-colorschemes/after,~/.vim/bundle/vim-colors-solarized/after,~/.vim/bundle/clang_complete/after,~/.vim/bundle/supertab/after,~/.vim/bundle/ultisnips/after,~/.vim/bundle/vim-snippets/after,~/.vim/bundle/vim-markdown/after,~/.vim/bundle/vim-surround/after,~/.vim/bundle/targets.vim/after,~/.vim/bundle/vim-repeat/after,~/.vim/bundle/vim-commentary/after
set scrolloff=999
set sessionoptions=blank,buffers,folds,help,options,tabpages,winsize,sesdir
set showcmd
set showmatch
set splitright
set textwidth=80
set ttimeoutlen=100
set visualbell
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
exe "cd " . escape(expand("<sfile>:p:h"), ' ')
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
badd +1 include/ccbase/mpl/functional.hpp
badd +1 include/ccbase/mpl
badd +11 include/ccbase/mpl.hpp
badd +11 include/ccbase/mpl/parse_wsv.hpp
badd +408 include/ccbase/mpl/list.hpp
badd +1 include/ccbase/mpl/constant.hpp
badd +95 include/ccbase/mpl/sequence_operations.hpp
badd +1 source/test/mpl_test.cpp
badd +478 include/ccbase/format/format_argument.hpp
badd +529 include/ccbase/format/format.hpp
badd +1 include/ccbase/format/attribute.hpp
badd +43 include/ccbase/format/argument_wrapper.hpp
badd +112 include/ccbase/format/formatter.hpp
badd +49 source/test/formatter_test.cpp
badd +1 source/test/format_argument_test.cpp
badd +26 include/ccbase/mpl/parse_natural.hpp
badd +11 Rakefile
badd +0 include/ccbase/platform/rotate.hpp
argglobal
silent! argdel *
argadd ~/projects/c++/ccbase/master/include/ccbase/mpl/functional.hpp
edit include/ccbase/platform/rotate.hpp
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd w
set nosplitbelow
wincmd t
set winheight=1 winwidth=1
exe 'vert 1resize ' . ((&columns * 101 + 102) / 204)
exe 'vert 2resize ' . ((&columns * 102 + 102) / 204)
argglobal
snoremap <buffer> <silent> 	 :python updateSnips()
nnoremap <buffer> <silent> 	 :python updateSnips()
xnoremap <buffer> <silent> 	 :python updateSnips()
onoremap <buffer> <silent> 	 :python updateSnips()
nnoremap <buffer> <silent>  
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s0:/*,mb:**,ex:*/,b://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
set concealcursor=vin
setlocal concealcursor=vin
set conceallevel=2
setlocal conceallevel=2
setlocal completefunc=ClangComplete
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
set cursorline
setlocal cursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=2croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
setlocal numberwidth=4
setlocal omnifunc=ClangComplete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal smartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=80
setlocal thesaurus=
setlocal noundofile
setlocal undolevels=-123456
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
argglobal
edit source/test/mpl_test.cpp
snoremap <buffer> <silent> 	 :python updateSnips()
nnoremap <buffer> <silent> 	 :python updateSnips()
xnoremap <buffer> <silent> 	 :python updateSnips()
onoremap <buffer> <silent> 	 :python updateSnips()
nnoremap <buffer> <silent>  
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal cindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s0:/*,mb:**,ex:*/,b://
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
set concealcursor=vin
setlocal concealcursor=vin
set conceallevel=2
setlocal conceallevel=2
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
set cursorline
setlocal cursorline
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal noexpandtab
if &filetype != 'cpp'
setlocal filetype=cpp
endif
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=0
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldmarker={{{,}}}
setlocal foldmethod=manual
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=foldtext()
setlocal formatexpr=
setlocal formatoptions=2croql
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=0
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
setlocal nolinebreak
setlocal nolisp
setlocal lispwords=
setlocal nolist
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=octal,hex
setlocal nonumber
setlocal numberwidth=4
setlocal omnifunc=ccomplete#Complete
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
setlocal norelativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal shiftwidth=8
setlocal noshortname
setlocal smartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'cpp'
setlocal syntax=cpp
endif
setlocal tabstop=8
setlocal tags=
setlocal textwidth=80
setlocal thesaurus=
setlocal noundofile
setlocal undolevels=-123456
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
silent! normal! zE
let s:l = 1 - ((0 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
1
normal! 0
wincmd w
exe 'vert 1resize ' . ((&columns * 101 + 102) / 204)
exe 'vert 2resize ' . ((&columns * 102 + 102) / 204)
tabnext 1
if exists('s:wipebuf')
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToO
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
