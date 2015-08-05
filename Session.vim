let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <S-Tab> <Plug>SuperTabBackward
inoremap <C-Tab> 	
inoremap <Right> <Nop>
inoremap <Left> <Nop>
inoremap <Down> <Nop>
inoremap <Up> <Nop>
map! <D-v> *
nnoremap <silent>  :nohl
vnoremap < <gv
vnoremap > >gv
xnoremap <silent> <expr> A targets#e('A')
onoremap <silent> Ala :call targets#o('alA', v:count1)
onoremap <silent> Ana :call targets#o('anA', v:count1)
onoremap <silent> Aa :call targets#o('acA', v:count1)
onoremap <silent> AL$ :call targets#o('$LA', v:count1)
onoremap <silent> AN$ :call targets#o('$NA', v:count1)
onoremap <silent> Al$ :call targets#o('$lA', v:count1)
onoremap <silent> An$ :call targets#o('$nA', v:count1)
onoremap <silent> A$ :call targets#o('$cA', v:count1)
onoremap <silent> AL& :call targets#o('&LA', v:count1)
onoremap <silent> AN& :call targets#o('&NA', v:count1)
onoremap <silent> Al& :call targets#o('&lA', v:count1)
onoremap <silent> An& :call targets#o('&nA', v:count1)
onoremap <silent> A& :call targets#o('&cA', v:count1)
onoremap <silent> AL| :call targets#o('|LA', v:count1)
onoremap <silent> AN| :call targets#o('|NA', v:count1)
onoremap <silent> Al| :call targets#o('|lA', v:count1)
onoremap <silent> An| :call targets#o('|nA', v:count1)
onoremap <silent> A| :call targets#o('|cA', v:count1)
onoremap <silent> AL\ :call targets#o('\LA', v:count1)
onoremap <silent> AN\ :call targets#o('\NA', v:count1)
onoremap <silent> Al\ :call targets#o('\lA', v:count1)
onoremap <silent> An\ :call targets#o('\nA', v:count1)
onoremap <silent> A\ :call targets#o('\cA', v:count1)
onoremap <silent> AL/ :call targets#o('/LA', v:count1)
onoremap <silent> AN/ :call targets#o('/NA', v:count1)
onoremap <silent> Al/ :call targets#o('/lA', v:count1)
onoremap <silent> An/ :call targets#o('/nA', v:count1)
onoremap <silent> A/ :call targets#o('/cA', v:count1)
onoremap <silent> AL# :call targets#o('#LA', v:count1)
onoremap <silent> AN# :call targets#o('#NA', v:count1)
onoremap <silent> Al# :call targets#o('#lA', v:count1)
onoremap <silent> An# :call targets#o('#nA', v:count1)
onoremap <silent> A# :call targets#o('#cA', v:count1)
onoremap <silent> AL* :call targets#o('*LA', v:count1)
onoremap <silent> AN* :call targets#o('*NA', v:count1)
onoremap <silent> Al* :call targets#o('*lA', v:count1)
onoremap <silent> An* :call targets#o('*nA', v:count1)
onoremap <silent> A* :call targets#o('*cA', v:count1)
onoremap <silent> AL_ :call targets#o('_LA', v:count1)
onoremap <silent> AN_ :call targets#o('_NA', v:count1)
onoremap <silent> Al_ :call targets#o('_lA', v:count1)
onoremap <silent> An_ :call targets#o('_nA', v:count1)
onoremap <silent> A_ :call targets#o('_cA', v:count1)
onoremap <silent> AL~ :call targets#o('~LA', v:count1)
onoremap <silent> AN~ :call targets#o('~NA', v:count1)
onoremap <silent> Al~ :call targets#o('~lA', v:count1)
onoremap <silent> An~ :call targets#o('~nA', v:count1)
onoremap <silent> A~ :call targets#o('~cA', v:count1)
onoremap <silent> AL= :call targets#o('=LA', v:count1)
onoremap <silent> AN= :call targets#o('=NA', v:count1)
onoremap <silent> Al= :call targets#o('=lA', v:count1)
onoremap <silent> An= :call targets#o('=nA', v:count1)
onoremap <silent> A= :call targets#o('=cA', v:count1)
onoremap <silent> AL- :call targets#o('-LA', v:count1)
onoremap <silent> AN- :call targets#o('-NA', v:count1)
onoremap <silent> Al- :call targets#o('-lA', v:count1)
onoremap <silent> An- :call targets#o('-nA', v:count1)
onoremap <silent> A- :call targets#o('-cA', v:count1)
onoremap <silent> AL+ :call targets#o('+LA', v:count1)
onoremap <silent> AN+ :call targets#o('+NA', v:count1)
onoremap <silent> Al+ :call targets#o('+lA', v:count1)
onoremap <silent> An+ :call targets#o('+nA', v:count1)
onoremap <silent> A+ :call targets#o('+cA', v:count1)
onoremap <silent> AL: :call targets#o(':LA', v:count1)
onoremap <silent> AN: :call targets#o(':NA', v:count1)
onoremap <silent> Al: :call targets#o(':lA', v:count1)
onoremap <silent> An: :call targets#o(':nA', v:count1)
onoremap <silent> A: :call targets#o(':cA', v:count1)
onoremap <silent> AL; :call targets#o(';LA', v:count1)
onoremap <silent> AN; :call targets#o(';NA', v:count1)
onoremap <silent> Al; :call targets#o(';lA', v:count1)
onoremap <silent> An; :call targets#o(';nA', v:count1)
onoremap <silent> A; :call targets#o(';cA', v:count1)
onoremap <silent> AL. :call targets#o('.LA', v:count1)
onoremap <silent> AN. :call targets#o('.NA', v:count1)
onoremap <silent> Al. :call targets#o('.lA', v:count1)
onoremap <silent> An. :call targets#o('.nA', v:count1)
onoremap <silent> A. :call targets#o('.cA', v:count1)
onoremap <silent> AL, :call targets#o(',LA', v:count1)
onoremap <silent> AN, :call targets#o(',NA', v:count1)
onoremap <silent> Al, :call targets#o(',lA', v:count1)
onoremap <silent> An, :call targets#o(',nA', v:count1)
onoremap <silent> A, :call targets#o(',cA', v:count1)
onoremap <silent> AL` :call targets#o('`LA', v:count1)
onoremap <silent> AN` :call targets#o('`NA', v:count1)
onoremap <silent> Al` :call targets#o('`lA', v:count1)
onoremap <silent> An` :call targets#o('`nA', v:count1)
onoremap <silent> A` :call targets#o('`cA', v:count1)
onoremap <silent> AL' :call targets#o('''LA', v:count1)
onoremap <silent> AN' :call targets#o('''NA', v:count1)
onoremap <silent> Al' :call targets#o('''lA', v:count1)
onoremap <silent> An' :call targets#o('''nA', v:count1)
onoremap <silent> A' :call targets#o('''cA', v:count1)
onoremap <silent> AL" :call targets#o('"LA', v:count1)
onoremap <silent> AN" :call targets#o('"NA', v:count1)
onoremap <silent> Al" :call targets#o('"lA', v:count1)
onoremap <silent> An" :call targets#o('"nA', v:count1)
onoremap <silent> A" :call targets#o('"cA', v:count1)
onoremap <silent> Alt :call targets#o('tlA', v:count1)
onoremap <silent> Ant :call targets#o('tnA', v:count1)
onoremap <silent> At :call targets#o('tcA', v:count1)
onoremap <silent> Al> :call targets#o('>lA', v:count1)
onoremap <silent> An> :call targets#o('>nA', v:count1)
onoremap <silent> A> :call targets#o('>cA', v:count1)
onoremap <silent> Al< :call targets#o('<lA', v:count1)
onoremap <silent> An< :call targets#o('<nA', v:count1)
onoremap <silent> A< :call targets#o('<cA', v:count1)
onoremap <silent> Al] :call targets#o(']lA', v:count1)
onoremap <silent> An] :call targets#o(']nA', v:count1)
onoremap <silent> A] :call targets#o(']cA', v:count1)
onoremap <silent> Al[ :call targets#o('[lA', v:count1)
onoremap <silent> An[ :call targets#o('[nA', v:count1)
onoremap <silent> A[ :call targets#o('[cA', v:count1)
onoremap <silent> AlB :call targets#o('BlA', v:count1)
onoremap <silent> AnB :call targets#o('BnA', v:count1)
onoremap <silent> AB :call targets#o('BcA', v:count1)
onoremap <silent> Al} :call targets#o('}lA', v:count1)
onoremap <silent> An} :call targets#o('}nA', v:count1)
onoremap <silent> A} :call targets#o('}cA', v:count1)
onoremap <silent> Al{ :call targets#o('{lA', v:count1)
onoremap <silent> An{ :call targets#o('{nA', v:count1)
onoremap <silent> A{ :call targets#o('{cA', v:count1)
onoremap <silent> Alb :call targets#o('blA', v:count1)
onoremap <silent> Anb :call targets#o('bnA', v:count1)
onoremap <silent> Ab :call targets#o('bcA', v:count1)
onoremap <silent> Al) :call targets#o(')lA', v:count1)
onoremap <silent> An) :call targets#o(')nA', v:count1)
onoremap <silent> A) :call targets#o(')cA', v:count1)
onoremap <silent> Al( :call targets#o('(lA', v:count1)
onoremap <silent> An( :call targets#o('(nA', v:count1)
onoremap <silent> A( :call targets#o('(cA', v:count1)
xnoremap <silent> <expr> I targets#e('I')
onoremap <silent> Ila :call targets#o('alI', v:count1)
onoremap <silent> Ina :call targets#o('anI', v:count1)
onoremap <silent> Ia :call targets#o('acI', v:count1)
onoremap <silent> IL$ :call targets#o('$LI', v:count1)
onoremap <silent> IN$ :call targets#o('$NI', v:count1)
onoremap <silent> Il$ :call targets#o('$lI', v:count1)
onoremap <silent> In$ :call targets#o('$nI', v:count1)
onoremap <silent> I$ :call targets#o('$cI', v:count1)
onoremap <silent> IL& :call targets#o('&LI', v:count1)
onoremap <silent> IN& :call targets#o('&NI', v:count1)
onoremap <silent> Il& :call targets#o('&lI', v:count1)
onoremap <silent> In& :call targets#o('&nI', v:count1)
onoremap <silent> I& :call targets#o('&cI', v:count1)
onoremap <silent> IL| :call targets#o('|LI', v:count1)
onoremap <silent> IN| :call targets#o('|NI', v:count1)
onoremap <silent> Il| :call targets#o('|lI', v:count1)
onoremap <silent> In| :call targets#o('|nI', v:count1)
onoremap <silent> I| :call targets#o('|cI', v:count1)
onoremap <silent> IL\ :call targets#o('\LI', v:count1)
onoremap <silent> IN\ :call targets#o('\NI', v:count1)
onoremap <silent> Il\ :call targets#o('\lI', v:count1)
onoremap <silent> In\ :call targets#o('\nI', v:count1)
onoremap <silent> I\ :call targets#o('\cI', v:count1)
onoremap <silent> IL/ :call targets#o('/LI', v:count1)
onoremap <silent> IN/ :call targets#o('/NI', v:count1)
onoremap <silent> Il/ :call targets#o('/lI', v:count1)
onoremap <silent> In/ :call targets#o('/nI', v:count1)
onoremap <silent> I/ :call targets#o('/cI', v:count1)
onoremap <silent> IL# :call targets#o('#LI', v:count1)
onoremap <silent> IN# :call targets#o('#NI', v:count1)
onoremap <silent> Il# :call targets#o('#lI', v:count1)
onoremap <silent> In# :call targets#o('#nI', v:count1)
onoremap <silent> I# :call targets#o('#cI', v:count1)
onoremap <silent> IL* :call targets#o('*LI', v:count1)
onoremap <silent> IN* :call targets#o('*NI', v:count1)
onoremap <silent> Il* :call targets#o('*lI', v:count1)
onoremap <silent> In* :call targets#o('*nI', v:count1)
onoremap <silent> I* :call targets#o('*cI', v:count1)
onoremap <silent> IL_ :call targets#o('_LI', v:count1)
onoremap <silent> IN_ :call targets#o('_NI', v:count1)
onoremap <silent> Il_ :call targets#o('_lI', v:count1)
onoremap <silent> In_ :call targets#o('_nI', v:count1)
onoremap <silent> I_ :call targets#o('_cI', v:count1)
onoremap <silent> IL~ :call targets#o('~LI', v:count1)
onoremap <silent> IN~ :call targets#o('~NI', v:count1)
onoremap <silent> Il~ :call targets#o('~lI', v:count1)
onoremap <silent> In~ :call targets#o('~nI', v:count1)
onoremap <silent> I~ :call targets#o('~cI', v:count1)
onoremap <silent> IL= :call targets#o('=LI', v:count1)
onoremap <silent> IN= :call targets#o('=NI', v:count1)
onoremap <silent> Il= :call targets#o('=lI', v:count1)
onoremap <silent> In= :call targets#o('=nI', v:count1)
onoremap <silent> I= :call targets#o('=cI', v:count1)
onoremap <silent> IL- :call targets#o('-LI', v:count1)
onoremap <silent> IN- :call targets#o('-NI', v:count1)
onoremap <silent> Il- :call targets#o('-lI', v:count1)
onoremap <silent> In- :call targets#o('-nI', v:count1)
onoremap <silent> I- :call targets#o('-cI', v:count1)
onoremap <silent> IL+ :call targets#o('+LI', v:count1)
onoremap <silent> IN+ :call targets#o('+NI', v:count1)
onoremap <silent> Il+ :call targets#o('+lI', v:count1)
onoremap <silent> In+ :call targets#o('+nI', v:count1)
onoremap <silent> I+ :call targets#o('+cI', v:count1)
onoremap <silent> IL: :call targets#o(':LI', v:count1)
onoremap <silent> IN: :call targets#o(':NI', v:count1)
onoremap <silent> Il: :call targets#o(':lI', v:count1)
onoremap <silent> In: :call targets#o(':nI', v:count1)
onoremap <silent> I: :call targets#o(':cI', v:count1)
onoremap <silent> IL; :call targets#o(';LI', v:count1)
onoremap <silent> IN; :call targets#o(';NI', v:count1)
onoremap <silent> Il; :call targets#o(';lI', v:count1)
onoremap <silent> In; :call targets#o(';nI', v:count1)
onoremap <silent> I; :call targets#o(';cI', v:count1)
onoremap <silent> IL. :call targets#o('.LI', v:count1)
onoremap <silent> IN. :call targets#o('.NI', v:count1)
onoremap <silent> Il. :call targets#o('.lI', v:count1)
onoremap <silent> In. :call targets#o('.nI', v:count1)
onoremap <silent> I. :call targets#o('.cI', v:count1)
onoremap <silent> IL, :call targets#o(',LI', v:count1)
onoremap <silent> IN, :call targets#o(',NI', v:count1)
onoremap <silent> Il, :call targets#o(',lI', v:count1)
onoremap <silent> In, :call targets#o(',nI', v:count1)
onoremap <silent> I, :call targets#o(',cI', v:count1)
onoremap <silent> IL` :call targets#o('`LI', v:count1)
onoremap <silent> IN` :call targets#o('`NI', v:count1)
onoremap <silent> Il` :call targets#o('`lI', v:count1)
onoremap <silent> In` :call targets#o('`nI', v:count1)
onoremap <silent> I` :call targets#o('`cI', v:count1)
onoremap <silent> IL' :call targets#o('''LI', v:count1)
onoremap <silent> IN' :call targets#o('''NI', v:count1)
onoremap <silent> Il' :call targets#o('''lI', v:count1)
onoremap <silent> In' :call targets#o('''nI', v:count1)
onoremap <silent> I' :call targets#o('''cI', v:count1)
onoremap <silent> IL" :call targets#o('"LI', v:count1)
onoremap <silent> IN" :call targets#o('"NI', v:count1)
onoremap <silent> Il" :call targets#o('"lI', v:count1)
onoremap <silent> In" :call targets#o('"nI', v:count1)
onoremap <silent> I" :call targets#o('"cI', v:count1)
onoremap <silent> Ilt :call targets#o('tlI', v:count1)
onoremap <silent> Int :call targets#o('tnI', v:count1)
onoremap <silent> It :call targets#o('tcI', v:count1)
onoremap <silent> Il> :call targets#o('>lI', v:count1)
onoremap <silent> In> :call targets#o('>nI', v:count1)
onoremap <silent> I> :call targets#o('>cI', v:count1)
onoremap <silent> Il< :call targets#o('<lI', v:count1)
onoremap <silent> In< :call targets#o('<nI', v:count1)
onoremap <silent> I< :call targets#o('<cI', v:count1)
onoremap <silent> Il] :call targets#o(']lI', v:count1)
onoremap <silent> In] :call targets#o(']nI', v:count1)
onoremap <silent> I] :call targets#o(']cI', v:count1)
onoremap <silent> Il[ :call targets#o('[lI', v:count1)
onoremap <silent> In[ :call targets#o('[nI', v:count1)
onoremap <silent> I[ :call targets#o('[cI', v:count1)
onoremap <silent> IlB :call targets#o('BlI', v:count1)
onoremap <silent> InB :call targets#o('BnI', v:count1)
onoremap <silent> IB :call targets#o('BcI', v:count1)
onoremap <silent> Il} :call targets#o('}lI', v:count1)
onoremap <silent> In} :call targets#o('}nI', v:count1)
onoremap <silent> I} :call targets#o('}cI', v:count1)
onoremap <silent> Il{ :call targets#o('{lI', v:count1)
onoremap <silent> In{ :call targets#o('{nI', v:count1)
onoremap <silent> I{ :call targets#o('{cI', v:count1)
onoremap <silent> Ilb :call targets#o('blI', v:count1)
onoremap <silent> Inb :call targets#o('bnI', v:count1)
onoremap <silent> Ib :call targets#o('bcI', v:count1)
onoremap <silent> Il) :call targets#o(')lI', v:count1)
onoremap <silent> In) :call targets#o(')nI', v:count1)
onoremap <silent> I) :call targets#o(')cI', v:count1)
onoremap <silent> Il( :call targets#o('(lI', v:count1)
onoremap <silent> In( :call targets#o('(nI', v:count1)
onoremap <silent> I( :call targets#o('(cI', v:count1)
xmap S <Plug>VSurround
nmap \\u <Plug>CommentaryUndo:echomsg '\\ is deprecated. Use gc'
nmap \\\ <Plug>CommentaryLine:echomsg '\\ is deprecated. Use gc'
nmap \\ :echomsg '\\ is deprecated. Use gc'<Plug>Commentary
xmap \\ <Plug>Commentary:echomsg '\\ is deprecated. Use gc'
xnoremap <silent> <expr> a targets#e('a')
onoremap <silent> ala :call targets#o('ala', v:count1)
onoremap <silent> ana :call targets#o('ana', v:count1)
onoremap <silent> aa :call targets#o('aca', v:count1)
onoremap <silent> aL$ :call targets#o('$La', v:count1)
onoremap <silent> aN$ :call targets#o('$Na', v:count1)
onoremap <silent> al$ :call targets#o('$la', v:count1)
onoremap <silent> an$ :call targets#o('$na', v:count1)
onoremap <silent> a$ :call targets#o('$ca', v:count1)
onoremap <silent> aL& :call targets#o('&La', v:count1)
onoremap <silent> aN& :call targets#o('&Na', v:count1)
onoremap <silent> al& :call targets#o('&la', v:count1)
onoremap <silent> an& :call targets#o('&na', v:count1)
onoremap <silent> a& :call targets#o('&ca', v:count1)
onoremap <silent> aL| :call targets#o('|La', v:count1)
onoremap <silent> aN| :call targets#o('|Na', v:count1)
onoremap <silent> al| :call targets#o('|la', v:count1)
onoremap <silent> an| :call targets#o('|na', v:count1)
onoremap <silent> a| :call targets#o('|ca', v:count1)
onoremap <silent> aL\ :call targets#o('\La', v:count1)
onoremap <silent> aN\ :call targets#o('\Na', v:count1)
onoremap <silent> al\ :call targets#o('\la', v:count1)
onoremap <silent> an\ :call targets#o('\na', v:count1)
onoremap <silent> a\ :call targets#o('\ca', v:count1)
onoremap <silent> aL/ :call targets#o('/La', v:count1)
onoremap <silent> aN/ :call targets#o('/Na', v:count1)
onoremap <silent> al/ :call targets#o('/la', v:count1)
onoremap <silent> an/ :call targets#o('/na', v:count1)
onoremap <silent> a/ :call targets#o('/ca', v:count1)
onoremap <silent> aL# :call targets#o('#La', v:count1)
onoremap <silent> aN# :call targets#o('#Na', v:count1)
onoremap <silent> al# :call targets#o('#la', v:count1)
onoremap <silent> an# :call targets#o('#na', v:count1)
onoremap <silent> a# :call targets#o('#ca', v:count1)
onoremap <silent> aL* :call targets#o('*La', v:count1)
onoremap <silent> aN* :call targets#o('*Na', v:count1)
onoremap <silent> al* :call targets#o('*la', v:count1)
onoremap <silent> an* :call targets#o('*na', v:count1)
onoremap <silent> a* :call targets#o('*ca', v:count1)
onoremap <silent> aL_ :call targets#o('_La', v:count1)
onoremap <silent> aN_ :call targets#o('_Na', v:count1)
onoremap <silent> al_ :call targets#o('_la', v:count1)
onoremap <silent> an_ :call targets#o('_na', v:count1)
onoremap <silent> a_ :call targets#o('_ca', v:count1)
onoremap <silent> aL~ :call targets#o('~La', v:count1)
onoremap <silent> aN~ :call targets#o('~Na', v:count1)
onoremap <silent> al~ :call targets#o('~la', v:count1)
onoremap <silent> an~ :call targets#o('~na', v:count1)
onoremap <silent> a~ :call targets#o('~ca', v:count1)
onoremap <silent> aL= :call targets#o('=La', v:count1)
onoremap <silent> aN= :call targets#o('=Na', v:count1)
onoremap <silent> al= :call targets#o('=la', v:count1)
onoremap <silent> an= :call targets#o('=na', v:count1)
onoremap <silent> a= :call targets#o('=ca', v:count1)
onoremap <silent> aL- :call targets#o('-La', v:count1)
onoremap <silent> aN- :call targets#o('-Na', v:count1)
onoremap <silent> al- :call targets#o('-la', v:count1)
onoremap <silent> an- :call targets#o('-na', v:count1)
onoremap <silent> a- :call targets#o('-ca', v:count1)
onoremap <silent> aL+ :call targets#o('+La', v:count1)
onoremap <silent> aN+ :call targets#o('+Na', v:count1)
onoremap <silent> al+ :call targets#o('+la', v:count1)
onoremap <silent> an+ :call targets#o('+na', v:count1)
onoremap <silent> a+ :call targets#o('+ca', v:count1)
onoremap <silent> aL: :call targets#o(':La', v:count1)
onoremap <silent> aN: :call targets#o(':Na', v:count1)
onoremap <silent> al: :call targets#o(':la', v:count1)
onoremap <silent> an: :call targets#o(':na', v:count1)
onoremap <silent> a: :call targets#o(':ca', v:count1)
onoremap <silent> aL; :call targets#o(';La', v:count1)
onoremap <silent> aN; :call targets#o(';Na', v:count1)
onoremap <silent> al; :call targets#o(';la', v:count1)
onoremap <silent> an; :call targets#o(';na', v:count1)
onoremap <silent> a; :call targets#o(';ca', v:count1)
onoremap <silent> aL. :call targets#o('.La', v:count1)
onoremap <silent> aN. :call targets#o('.Na', v:count1)
onoremap <silent> al. :call targets#o('.la', v:count1)
onoremap <silent> an. :call targets#o('.na', v:count1)
onoremap <silent> a. :call targets#o('.ca', v:count1)
onoremap <silent> aL, :call targets#o(',La', v:count1)
onoremap <silent> aN, :call targets#o(',Na', v:count1)
onoremap <silent> al, :call targets#o(',la', v:count1)
onoremap <silent> an, :call targets#o(',na', v:count1)
onoremap <silent> a, :call targets#o(',ca', v:count1)
onoremap <silent> aL` :call targets#o('`La', v:count1)
onoremap <silent> aN` :call targets#o('`Na', v:count1)
onoremap <silent> al` :call targets#o('`la', v:count1)
onoremap <silent> an` :call targets#o('`na', v:count1)
onoremap <silent> a` :call targets#o('`ca', v:count1)
onoremap <silent> aL' :call targets#o('''La', v:count1)
onoremap <silent> aN' :call targets#o('''Na', v:count1)
onoremap <silent> al' :call targets#o('''la', v:count1)
onoremap <silent> an' :call targets#o('''na', v:count1)
onoremap <silent> a' :call targets#o('''ca', v:count1)
onoremap <silent> aL" :call targets#o('"La', v:count1)
onoremap <silent> aN" :call targets#o('"Na', v:count1)
onoremap <silent> al" :call targets#o('"la', v:count1)
onoremap <silent> an" :call targets#o('"na', v:count1)
onoremap <silent> a" :call targets#o('"ca', v:count1)
onoremap <silent> alt :call targets#o('tla', v:count1)
onoremap <silent> ant :call targets#o('tna', v:count1)
onoremap <silent> at :call targets#o('tca', v:count1)
onoremap <silent> al> :call targets#o('>la', v:count1)
onoremap <silent> an> :call targets#o('>na', v:count1)
onoremap <silent> a> :call targets#o('>ca', v:count1)
onoremap <silent> al< :call targets#o('<la', v:count1)
onoremap <silent> an< :call targets#o('<na', v:count1)
onoremap <silent> a< :call targets#o('<ca', v:count1)
onoremap <silent> al] :call targets#o(']la', v:count1)
onoremap <silent> an] :call targets#o(']na', v:count1)
onoremap <silent> a] :call targets#o(']ca', v:count1)
onoremap <silent> al[ :call targets#o('[la', v:count1)
onoremap <silent> an[ :call targets#o('[na', v:count1)
onoremap <silent> a[ :call targets#o('[ca', v:count1)
onoremap <silent> alB :call targets#o('Bla', v:count1)
onoremap <silent> anB :call targets#o('Bna', v:count1)
onoremap <silent> aB :call targets#o('Bca', v:count1)
onoremap <silent> al} :call targets#o('}la', v:count1)
onoremap <silent> an} :call targets#o('}na', v:count1)
onoremap <silent> a} :call targets#o('}ca', v:count1)
onoremap <silent> al{ :call targets#o('{la', v:count1)
onoremap <silent> an{ :call targets#o('{na', v:count1)
onoremap <silent> a{ :call targets#o('{ca', v:count1)
onoremap <silent> alb :call targets#o('bla', v:count1)
onoremap <silent> anb :call targets#o('bna', v:count1)
onoremap <silent> ab :call targets#o('bca', v:count1)
onoremap <silent> al) :call targets#o(')la', v:count1)
onoremap <silent> an) :call targets#o(')na', v:count1)
onoremap <silent> a) :call targets#o(')ca', v:count1)
onoremap <silent> al( :call targets#o('(la', v:count1)
onoremap <silent> an( :call targets#o('(na', v:count1)
onoremap <silent> a( :call targets#o('(ca', v:count1)
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
xnoremap <silent> <expr> i targets#e('i')
onoremap <silent> ila :call targets#o('ali', v:count1)
onoremap <silent> ina :call targets#o('ani', v:count1)
onoremap <silent> ia :call targets#o('aci', v:count1)
onoremap <silent> iL$ :call targets#o('$Li', v:count1)
onoremap <silent> iN$ :call targets#o('$Ni', v:count1)
onoremap <silent> il$ :call targets#o('$li', v:count1)
onoremap <silent> in$ :call targets#o('$ni', v:count1)
onoremap <silent> i$ :call targets#o('$ci', v:count1)
onoremap <silent> iL& :call targets#o('&Li', v:count1)
onoremap <silent> iN& :call targets#o('&Ni', v:count1)
onoremap <silent> il& :call targets#o('&li', v:count1)
onoremap <silent> in& :call targets#o('&ni', v:count1)
onoremap <silent> i& :call targets#o('&ci', v:count1)
onoremap <silent> iL| :call targets#o('|Li', v:count1)
onoremap <silent> iN| :call targets#o('|Ni', v:count1)
onoremap <silent> il| :call targets#o('|li', v:count1)
onoremap <silent> in| :call targets#o('|ni', v:count1)
onoremap <silent> i| :call targets#o('|ci', v:count1)
onoremap <silent> iL\ :call targets#o('\Li', v:count1)
onoremap <silent> iN\ :call targets#o('\Ni', v:count1)
onoremap <silent> il\ :call targets#o('\li', v:count1)
onoremap <silent> in\ :call targets#o('\ni', v:count1)
onoremap <silent> i\ :call targets#o('\ci', v:count1)
onoremap <silent> iL/ :call targets#o('/Li', v:count1)
onoremap <silent> iN/ :call targets#o('/Ni', v:count1)
onoremap <silent> il/ :call targets#o('/li', v:count1)
onoremap <silent> in/ :call targets#o('/ni', v:count1)
onoremap <silent> i/ :call targets#o('/ci', v:count1)
onoremap <silent> iL# :call targets#o('#Li', v:count1)
onoremap <silent> iN# :call targets#o('#Ni', v:count1)
onoremap <silent> il# :call targets#o('#li', v:count1)
onoremap <silent> in# :call targets#o('#ni', v:count1)
onoremap <silent> i# :call targets#o('#ci', v:count1)
onoremap <silent> iL* :call targets#o('*Li', v:count1)
onoremap <silent> iN* :call targets#o('*Ni', v:count1)
onoremap <silent> il* :call targets#o('*li', v:count1)
onoremap <silent> in* :call targets#o('*ni', v:count1)
onoremap <silent> i* :call targets#o('*ci', v:count1)
onoremap <silent> iL_ :call targets#o('_Li', v:count1)
onoremap <silent> iN_ :call targets#o('_Ni', v:count1)
onoremap <silent> il_ :call targets#o('_li', v:count1)
onoremap <silent> in_ :call targets#o('_ni', v:count1)
onoremap <silent> i_ :call targets#o('_ci', v:count1)
onoremap <silent> iL~ :call targets#o('~Li', v:count1)
onoremap <silent> iN~ :call targets#o('~Ni', v:count1)
onoremap <silent> il~ :call targets#o('~li', v:count1)
onoremap <silent> in~ :call targets#o('~ni', v:count1)
onoremap <silent> i~ :call targets#o('~ci', v:count1)
onoremap <silent> iL= :call targets#o('=Li', v:count1)
onoremap <silent> iN= :call targets#o('=Ni', v:count1)
onoremap <silent> il= :call targets#o('=li', v:count1)
onoremap <silent> in= :call targets#o('=ni', v:count1)
onoremap <silent> i= :call targets#o('=ci', v:count1)
onoremap <silent> iL- :call targets#o('-Li', v:count1)
onoremap <silent> iN- :call targets#o('-Ni', v:count1)
onoremap <silent> il- :call targets#o('-li', v:count1)
onoremap <silent> in- :call targets#o('-ni', v:count1)
onoremap <silent> i- :call targets#o('-ci', v:count1)
onoremap <silent> iL+ :call targets#o('+Li', v:count1)
onoremap <silent> iN+ :call targets#o('+Ni', v:count1)
onoremap <silent> il+ :call targets#o('+li', v:count1)
onoremap <silent> in+ :call targets#o('+ni', v:count1)
onoremap <silent> i+ :call targets#o('+ci', v:count1)
onoremap <silent> iL: :call targets#o(':Li', v:count1)
onoremap <silent> iN: :call targets#o(':Ni', v:count1)
onoremap <silent> il: :call targets#o(':li', v:count1)
onoremap <silent> in: :call targets#o(':ni', v:count1)
onoremap <silent> i: :call targets#o(':ci', v:count1)
onoremap <silent> iL; :call targets#o(';Li', v:count1)
onoremap <silent> iN; :call targets#o(';Ni', v:count1)
onoremap <silent> il; :call targets#o(';li', v:count1)
onoremap <silent> in; :call targets#o(';ni', v:count1)
onoremap <silent> i; :call targets#o(';ci', v:count1)
onoremap <silent> iL. :call targets#o('.Li', v:count1)
onoremap <silent> iN. :call targets#o('.Ni', v:count1)
onoremap <silent> il. :call targets#o('.li', v:count1)
onoremap <silent> in. :call targets#o('.ni', v:count1)
onoremap <silent> i. :call targets#o('.ci', v:count1)
onoremap <silent> iL, :call targets#o(',Li', v:count1)
onoremap <silent> iN, :call targets#o(',Ni', v:count1)
onoremap <silent> il, :call targets#o(',li', v:count1)
onoremap <silent> in, :call targets#o(',ni', v:count1)
onoremap <silent> i, :call targets#o(',ci', v:count1)
onoremap <silent> iL` :call targets#o('`Li', v:count1)
onoremap <silent> iN` :call targets#o('`Ni', v:count1)
onoremap <silent> il` :call targets#o('`li', v:count1)
onoremap <silent> in` :call targets#o('`ni', v:count1)
onoremap <silent> i` :call targets#o('`ci', v:count1)
onoremap <silent> iL' :call targets#o('''Li', v:count1)
onoremap <silent> iN' :call targets#o('''Ni', v:count1)
onoremap <silent> il' :call targets#o('''li', v:count1)
onoremap <silent> in' :call targets#o('''ni', v:count1)
onoremap <silent> i' :call targets#o('''ci', v:count1)
onoremap <silent> iL" :call targets#o('"Li', v:count1)
onoremap <silent> iN" :call targets#o('"Ni', v:count1)
onoremap <silent> il" :call targets#o('"li', v:count1)
onoremap <silent> in" :call targets#o('"ni', v:count1)
onoremap <silent> i" :call targets#o('"ci', v:count1)
onoremap <silent> ilt :call targets#o('tli', v:count1)
onoremap <silent> int :call targets#o('tni', v:count1)
onoremap <silent> it :call targets#o('tci', v:count1)
onoremap <silent> il> :call targets#o('>li', v:count1)
onoremap <silent> in> :call targets#o('>ni', v:count1)
onoremap <silent> i> :call targets#o('>ci', v:count1)
onoremap <silent> il< :call targets#o('<li', v:count1)
onoremap <silent> in< :call targets#o('<ni', v:count1)
onoremap <silent> i< :call targets#o('<ci', v:count1)
onoremap <silent> il] :call targets#o(']li', v:count1)
onoremap <silent> in] :call targets#o(']ni', v:count1)
onoremap <silent> i] :call targets#o(']ci', v:count1)
onoremap <silent> il[ :call targets#o('[li', v:count1)
onoremap <silent> in[ :call targets#o('[ni', v:count1)
onoremap <silent> i[ :call targets#o('[ci', v:count1)
onoremap <silent> ilB :call targets#o('Bli', v:count1)
onoremap <silent> inB :call targets#o('Bni', v:count1)
onoremap <silent> iB :call targets#o('Bci', v:count1)
onoremap <silent> il} :call targets#o('}li', v:count1)
onoremap <silent> in} :call targets#o('}ni', v:count1)
onoremap <silent> i} :call targets#o('}ci', v:count1)
onoremap <silent> il{ :call targets#o('{li', v:count1)
onoremap <silent> in{ :call targets#o('{ni', v:count1)
onoremap <silent> i{ :call targets#o('{ci', v:count1)
onoremap <silent> ilb :call targets#o('bli', v:count1)
onoremap <silent> inb :call targets#o('bni', v:count1)
onoremap <silent> ib :call targets#o('bci', v:count1)
onoremap <silent> il) :call targets#o(')li', v:count1)
onoremap <silent> in) :call targets#o(')ni', v:count1)
onoremap <silent> i) :call targets#o(')ci', v:count1)
onoremap <silent> il( :call targets#o('(li', v:count1)
onoremap <silent> in( :call targets#o('(ni', v:count1)
onoremap <silent> i( :call targets#o('(ci', v:count1)
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
vmap <BS> "-d
vmap <D-x> "*d
vmap <D-c> "*y
vmap <D-v> "-d"*P
nmap <D-v> "*P
imap S <Plug>ISurround
imap s <Plug>Isurround
imap 	 <Plug>SuperTabForward
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
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/vim-colorschemes,~/.vim/bundle/vim-colors-solarized,~/.vim/bundle/xoria_lite,~/.vim/bundle/vim-markdown,~/.vim/bundle/clang_complete,~/.vim/bundle/supertab,~/.vim/bundle/vim-snippets,~/.vim/bundle/smartfile,~/.vim/bundle/tabular,~/.vim/bundle/rename.vim,~/.vim/bundle/vim-surround,~/.vim/bundle/targets.vim,~/.vim/bundle/vim-repeat,~/.vim/bundle/vim-commentary,/opt/local/share/vim/vimfiles,/opt/local/share/vim/vim74,/opt/local/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/vim-colorschemes/after,~/.vim/bundle/vim-colors-solarized/after,~/.vim/bundle/xoria_lite/after,~/.vim/bundle/vim-markdown/after,~/.vim/bundle/clang_complete/after,~/.vim/bundle/supertab/after,~/.vim/bundle/vim-snippets/after,~/.vim/bundle/smartfile/after,~/.vim/bundle/tabular/after,~/.vim/bundle/rename.vim/after,~/.vim/bundle/vim-surround/after,~/.vim/bundle/targets.vim/after,~/.vim/bundle/vim-repeat/after,~/.vim/bundle/vim-commentary/a
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
badd +1 include/ccbase/dynamic/load.hpp
badd +1 include/ccbase/dynamic/visibility.hpp
badd +1 include/ccbase/error/expected.hpp
badd +1 include/ccbase/filesystem/directory_entry.hpp
badd +1 include/ccbase/filesystem/directory_iterator.hpp
badd +1 include/ccbase/filesystem/glob_matcher.hpp
badd +1 include/ccbase/filesystem/range.hpp
badd +1 include/ccbase/filesystem/system_call.hpp
badd +1 include/ccbase/format/argument_wrapper.hpp
badd +1 include/ccbase/format/attribute.hpp
badd +1 include/ccbase/format/format.hpp
badd +1 include/ccbase/format/formatter.hpp
badd +1 include/ccbase/format/format_argument.hpp
badd +1 include/ccbase/format/printable_types.hpp
badd +1 include/ccbase/mpl/constant.hpp
badd +219 include/ccbase/mpl/functional.hpp
badd +1 include/ccbase/mpl/list.hpp
badd +1 include/ccbase/platform/attributes.hpp
badd +1 include/ccbase/platform/bswap.hpp
badd +1 include/ccbase/platform/definitions.hpp
badd +1 include/ccbase/platform/identification.hpp
badd +1 include/ccbase/platform/rotate.hpp
badd +1 include/ccbase/platform/yield_execution.hpp
badd +1 include/ccbase/unit_test/module.hpp
badd +1 include/ccbase/unit_test/module_list.hpp
badd +1 include/ccbase/unit_test/result.hpp
badd +1 include/ccbase/unit_test/unit_test.hpp
badd +1 include/ccbase/utility/accessors.hpp
badd +1 include/ccbase/utility/bytes.hpp
badd +1 include/ccbase/utility/enum_bitmask.hpp
badd +1 source/test/dynamic_test.cpp
badd +1 source/test/expected_test.cpp
badd +1 source/test/filesystem_test.cpp
badd +1 source/test/formatter_test.cpp
badd +1 source/test/format_argument_test.cpp
badd +19 source/test/mpl_test.cpp
badd +1 source/test/platform_test.cpp
badd +1 source/test/unit_test_test.cpp
badd +1 .gitignore
badd +52 README.md
badd +11 Rakefile
badd +27 scratch.hpp
badd +1741 ~/scratch/meta.hpp
badd +119 include/ccbase/mpl/operations.hpp
badd +1 include/ccbase/mpl/list_operations.hpp
badd +14 include/ccbase/mpl.hpp
argglobal
silent! argdel *
argadd ~/projects/infancy/ndmath/ccbase/source/test/dynamic_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/expected_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/filesystem_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/formatter_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/format_argument_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/mpl_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/platform_test.cpp
argadd ~/projects/infancy/ndmath/ccbase/source/test/unit_test_test.cpp
edit include/ccbase/mpl/list_operations.hpp
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
edit include/ccbase/mpl/list_operations.hpp
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
let s:l = 154 - ((45 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
154
normal! 022|
wincmd w
argglobal
edit README.md
let s:cpo_save=&cpo
set cpo&vim
vmap <buffer> [] <Plug>Markdown_MoveToPreviousSiblingHeader
nmap <buffer> [] <Plug>Markdown_MoveToPreviousSiblingHeader
vmap <buffer> [[ <Plug>Markdown_MoveToPreviousHeader
nmap <buffer> [[ <Plug>Markdown_MoveToPreviousHeader
vmap <buffer> ]c <Plug>Markdown_MoveToCurHeader
nmap <buffer> ]c <Plug>Markdown_MoveToCurHeader
vmap <buffer> ]u <Plug>Markdown_MoveToParentHeader
nmap <buffer> ]u <Plug>Markdown_MoveToParentHeader
vmap <buffer> ][ <Plug>Markdown_MoveToNextSiblingHeader
nmap <buffer> ][ <Plug>Markdown_MoveToNextSiblingHeader
vmap <buffer> ]] <Plug>Markdown_MoveToNextHeader
nmap <buffer> ]] <Plug>Markdown_MoveToNextHeader
vmap <buffer> gx <Plug>Markdown_OpenUrlUnderCursor
nmap <buffer> gx <Plug>Markdown_OpenUrlUnderCursor
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal nobinary
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
setlocal colorcolumn=
setlocal comments=s0:<!--,mb:\ \ **,ex:-->
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
if &filetype != 'mkd'
setlocal filetype=mkd
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
setlocal formatoptions=tqo2r
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
setlocal omnifunc=
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
setlocal nosmartindent
setlocal softtabstop=0
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=
setlocal suffixesadd=
setlocal swapfile
setlocal synmaxcol=3000
if &syntax != 'mkd'
setlocal syntax=mkd
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
let s:l = 45 - ((35 * winheight(0) + 26) / 52)
if s:l < 1 | let s:l = 1 | endif
exe s:l
normal! zt
45
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
