.. _pointers:

Kazalci in reference
====================

Kazalci so malo podobni iteratorjem,
ki smo jih srečali že v poglavju :ref:`podatkovnitipi` / :ref:`iteratorjiuvod`,
reference pa smo že srečali v poglavju :ref:`funkcijecpp` / :ref:`referenceuvod`.

Reference
---------

Reference so spremenljivke, ki predstavljajo drugo ime za isto spremenljivko.
Če imamo spremenljivko tipa ``T``, ima referenca nanjo tip ``T&``.

.. code-block:: cpp

  int a = 7;
  int& b = a;
  a = 8;
  cout << a << " " << b << endl;
  b = 9;
  cout << a << " " << b << endl;

V zgornjem primeru je ``b`` referenca na ``a``, tako da ko spremenimo ``a``, se
spremeni tudi ``b`` in obratno. Tako se izpiše ``8 8`` in ``9 9``.

Lahko imamo tudi konstantne reference, to so reference, ki dovolijo spreminjanja
svoje vrednosti. Če imamo konstantno spremenljivko, lahko nanjo naredimo le
konstantno referenco, lahko pa konstantno referenco naredimo tudi na običajno
spremenljivko. O taki referenci razmišljamo kot o *pogledu* na spremenljivko,
saj lahko prek nje samo opazujemo, kaj se dogaja, ničesar pa ne moremo
spreminjati.

Referenca ne more biti prazna in vedno kaže na neko spremenljivko. Še vedno pa ne
na programerju, da pazi, da referenca kaže na veljavno spremenljivko, ki še ni
bila uničena. Tako npr. ne smemo iz funkcije vračati referenc na lokalne
spremenljivke. Primer reference na neveljavno spremenljivko:

.. code-block:: cpp

  int a = 7;
  int& b = a;
  { int c = 8; b = c; }
  cout << b << endl;

Spremenljivka ``b`` je referenca na ``c``, ki je že izbrisana. Program sicer v
veliko primerih pravilno izpiše 8, toda to ni zagotovljeno, se  splošnem ne
zgodi in se na tako obnašanje ne moremo zanašati. Zgornji program je preprosto
neveljaven, četudi občasno deluje.

.. note::

  Če definiramo več referenc na isti vrstici, moramo znak ``&`` ponoviti.

  .. code-block:: cpp

    int& r1 = v1, &r2 = v2, &r3 = v3;

  Zgornja koda ustvari tri reference ``r1, r2, r3`` na spremenljivke ``v1, v2,
  v3``.


Naslovi spremenljivk
--------------------
C++ programerju omogoča, da pogleda, na katerem naslovu v spominu je shranjena
določena spremenljivka. O strukturi spomina bomo govorili kasneje, sedaj povejmo
le, da si program predstavlja, kot da je spomnim dolga enodimenzionalna
tabela, razdeljena na celice po 1 bajt. Vrednost spremenljivke ``int a`` je
shranjena nekje v tej tabeli; ker je ``int`` ponavadi velik 4 bajte zavzema 4
bajte. S pomočjo *operatorja* ``&``, ki se mu reče operator "naslov od"
(*address of*) lahko dobimo naslov spremenljivke. Če spremenljivka zavzema več
kot eno celico, dobimo naslov prve celice, ki jo zavzema. Primer:

.. code-block:: cpp

  int a = 7;
  cout << &a << endl;

Zgornja koda izpiše naslov spremenljivke, nekaj podobnega ``0x7ffe78a6f354``,
kar je zaporedna številka (v šestnajstiškem sistemu) celice, kjer se ``a`` nahaja.
Naslov je vedno številka znane velikosti, praviloma 32 bitov na 32 bitnih
računalnikih in 64 bitov na 64 bitnih.

.. warning::

  Za ustvarjenje referenc uporabljamo enak znak ``&`` kot za pridobivanje
  naslovov spremeljivk, toda enkrat je ta sestavni del tipa spremenljivke,
  drugič pa nastopa kot operator, tako da je vedno možno iz konteksta ugotoviti,
  za katerega gre.


Kazalci
-------

Kazalci (*pointers*) izvirajo iz jezika C, predhodnika C++, in so v C-ju edini način, da
spremenimo vrednost parametra znotraj funkcije.
Kazalec na spremenljivko ``a`` tipa ``T`` je spremenljivka, katere tip se označi z
``T*`` in njena vrednost pa je naslov spremenljivke ``a``.
Primer definicije:

.. code-block:: cpp

  int a = 7;
  int* p = &a;
  cout << p << endl;

Zgornja koda izpiše nekaj podobnega  ``0x7ffe78a6f354``, saj je vrednost
spremenljivke ``p`` naslov spremenljivke ``a``. Pravimo, da je spremenljivka ``p``
kazalec na ``a``. Tip ``int*`` pomeni, da je vrednost, ki je na naslovu, ki je
shranjen v ``p``, v spominu shranjeno celo število. Ta tip nima direktne
povezave s tem, da je naslov sam po sebi tudi celo število, to je tako ali tako
vedno.

Najosnovnejša operacija na kazalcih je operacija, ki dobi vrednost na nekem naslovu.
Operacija se imenuje *value of* oz. dereferenca in se ga označi z ``*``.
Z njegovo pomočjo dobimo ali nastavimo vrednost na nekem mestu v spominu.
Primer:

.. code-block:: cpp

  double a = 7.5;
  double* p = &a;  // npr. 0x7ffe78a6f354
  cout << *p << endl;
  *p = 8.5;
  cout << a << endl;

Zgornji primer izpiše  ``7.5`` in ``8.5``, saj izraz ``*p = 8.5`` na mesto
``0x7ffe78a6f354`` (kjer je spremenljivka ``a``) shrani vrednosti ``8.5``.
Tukaj tudi vidimo, zakaj je dobro vedeti tip, na katerega kazalec kaže. Sama
vrednost ``0x7ffe78a6f354`` se namreč nanaša na prvi bajt spomina in
zaradi tipa ``double`` vemo, da moramo prebrati še naslednjih 7 in jih
interpretirati kot decimalno število.

.. note::

  Če definiramo več kazalcev na isti vrstici, moramo podobno kot pri referencah znak ``*`` ponoviti.

  .. code-block:: cpp

    int* p1 = &v1, *r2 = &v2, *r3 = &v3;

  Zgornja koda ustvari tri reference ``r1, r2, r3`` na spremenljivke ``v1, v2,
  v3``.

.. warning::

  Za ustvarjenje kazalcev uporabljamo enak znak ``*`` kot za dobivanje vrednosti
  na danem naslovu. Toda podobno kot pri referencah je enkrat ``*`` sestavni del
  tipa spremenljivke, drugič pa nastopa kot operator, tako da je vedno možno iz
  konteksta ugotoviti, za katerega gre.

vrednosti kazalcev so vedno naslovi, ki smo jih dobili iz obstoječe
spremenljivke ali sistema. Ne moremo npr. narediti kar

.. code-block:: cpp

  char* p = 20;
  *p = 'h';

da bi na mesto `20`` v spominu napisali znak ``h``. Že preajalnik se bo
pritožil

.. code-block:: none

  a.cpp:2:15: error: invalid conversion from ‘int’ to ‘char*’ [-fpermissive]
     char* p = 20;
               ^~

Če pa z eksplicitno pretvorbo to vseeno nastavimo, se program sesuje, saj
najverjetneje do celice 20 nimamo dostopa in dobimo napako ``[1]    24346
segmentation fault (core dumped)``.

Null pointer
~~~~~~~~~~~~

Z razliko od referenc kazalci lahko ne kažejo nikamor. To povemo tako, da jim
damo vrednost 0, ki predstavlja naslov ``0x000000000``, za kar imamo direktno
besedo ``nullptr``. Tako lahko naredimo

.. code-block:: cpp

  int* p = nullptr;

Če je ``p`` ničelni kazalec, je neveljavno pogledati rednost na tem mestu --
zagotovljeno je, da to vedno povzroči napako.

.. note::

  Nastaviti ``p`` na ``nullptr`` je drugače, kot pustiti nenastavljenega; v tem
  primeru bi bila njegova vrednost nenastavljena in bi bila karkoli je ostalo v
  spominu, kjer je bil ``p`` ustvarjen.


Delo s spominom
---------------

Spomin za spremenljivke v programih lahko dobimo na več načinov: pravimo da so
spremenljivke lahko na skladu (*stack*), ali pa na kopici (*heap*).
Obstajajo tudi drugi predeli, za npr. statične ali globalne spremenljivke, konstantne
podatke, itd..., s katerimi se zdaj ne bomo ukvarjali. Tako sklad kot
kopica sta dela RAMa, kjer lahko naredimo spremenljivke. Za običajne lokalne
spremenljivke je prostor rezerviran na skladu že med prevajanjem programa
in dostop do njih je ponavadi hitrejši. Če kličemo funkcijo, ki kliče funkcijo,
ki imajo vsaka svoje lokalne spremenljivke, se te nalagajo v spomin po vrsti
ko gremo globlje v klicih in sprostijo, ki se z njih vračajo.

Z razliko od sklada se alokacija na kopici dogaja med tekom programa,
spremenljivke na kopici so nepovezane med seboj, dostop do nje je ponavadi
počasnejši, ima pa mnogo več prostora, ki je omejen le z velikostjo virtualnega
spomina, ki je na voljo programu (beri: z velikostjo RAMa).
Spomin na kopici lahko zahtevamo od operacijskega sistema, ga poljubno
uporabljamo in lepo je, da ga na koncu tudi vrnemo.
V C-ju imamo za alokacijo in dealokacijo na voljo para funkcij ``malloc`` (*memory
allocation*) in ``free`` (in še nekaj drugih), v C++-u pa sta nadomeščeni z operatorji
``new``, ``new[]``, ``delete`` in ``delete[]``.
Verziji z ``[]`` sta namenjeni alokaciji tabel in se bomo z njimi ukvarjali
pozneje. Alokaciji spomina na kopici se pogosto reče tudi *dinamična alokacija*.

Alokacija spomina vrne kazalec na mesto v RAMu, kjer nam je bi dodeljen prostor
za spremenljivko. Če je bila alokacija neuspešna (npr. zmanjkalo nam je
spomina), C++ vrže izjemo tipa ``std::bad_alloc``. Obstaja več verzij operatorja
``new``, ki spomin alocirajo na različne načine, npr. brez metanja izjem,
na že določeno mesto, ali pa brez konstrukcije alociranega objekta, toda tudi v
to se ne bomo spuščali.

Primer običaje alokacije decimalnega števila:

.. code-block:: cpp

  int main() {
      double* p = new double(2.3);  // p ima vrednost 2.3
      double* q = new double();     // q ima vrednost 0.0
      double* r = new double;       // r ima nedefinirano vrednost
      // uporabljamo p, q, r
      delete p;  // vrnemo spomin sistemu
      delete q;
      delete r;
  }

Vsaki alokaciji mora, ko spomin nehamo uporabljati, slediti dealokacija spomina,
ki jo sprožimo z ``delete``. Tukaj se držimo enostavnega pravila: vsak
poklicani ``new`` mora imeni natanko en pripadajoči ``delete``, ki izbriše
spomin, dobljen s tem klicem ``new``.
Čeprav morda sintaksa ``delete p`` izgleda, kot da bi izbrisali spremenljivko
``p``, izbrišemo samo *spomin* na katerega ``p`` kaže, ``p`` pa ostane veljavna
in ji lahko damo neko novo vrednost (vanjo shranimo nek drug naslov). Ko
govorimo, pa se pogosto reče, da smo zbrisali ``p`` in se razume, da v resnimi
mislimo spomin na naslovu, shranjenem v ``p``.

Preden ga izbrišemo, lahko ``p``, ``q`` ali ``r`` uporabljamo kot vsak drug kazalec,
npr. nastavimo ``*p = 4.2``. Tako na roko kot zgoraj v C++ redko alociramo
spremenljivke, saj ponavadi uporabimo mehanizme, ki to počnejo namesto nas in
pri katerih se ne more zgoditi, da bi po nesreči pozabili poklicati ``delete``.
Prav tako pa ne smemo ``delete`` poklicati dvakrat. Primer, ko se nam to lahko
zgodi:

.. code-block:: cpp

  class A {
    public:
      int a;
  };

  int main() {
      A* a = new A();
      A* b = a;
      delete a;
      delete b;

      return 0;
  }

Pri klicu ``delete a`` se izbriše objekt na naslovu, shranjenemu v ``a``.
Toda spremenljivka ``b`` kaže na enak naslov, in ko pokličemo ``delete b``
sistem zopet poskuša izbrisati že izbrisan objekt na istem naslovu.
Kaj se ob tem zgodi ni definirano (*undefined behviour*), kar pomeni, da se ne
moremo zanašati na kakršnokoli deterministično obnašanje programa.
Lahko ni narobe nič, lahko se šele kasneje pokaže, da je šlo s spominom nekaj
narobe, lahko se program takoj sesuje. Najpogostejša napaka zgleda podobno

.. code-block:: none

  [1]    26815 segmentation fault (core dumped)  ./a

ali pa malo bolj informativno

.. code-block:: none

  *** glibc detected *** ./a: double free or corruption (fasttop): 0x01600008 ***
  ======= Backtrace: =========
  /lib/libc.so.6[0xb162e2d4]
  /lib/libc.so.6(cfree+0x9c)[0xb162287c]
  ./a[0x01600004]
  ./a[0x01600008]
  ======= Memory map: ========
  ...

Memory leak
~~~~~~~~~~~
Ena izmed pogostejših napak pri programiranju v C-ju in C++-u je
memory leak, kar se lahko prevede kot puščanje spomina. Ideja je, da programu
uhaja spomin, podobno kot iz slabo zategnjene vodovodne cevi pušča voda.
To se zgodi, če nekaj spomina od sistema zahtevamo, nanj pozabimo in ga nikoli
ne vrnemo. Če tak program teče dlje časa, porablja in zahteva čedalje več spomina,
in ga nič ne vrača, kar pomeni da ga nam nekoč zmanjka, računalnik začne
delovati zelo počasi in morda operacijski sistem naš program ubije, ali pa
postane tako neodziven, da je potrebno računalnik ponovno zagnati.
Memory leake je pogosto težko zaznati, saj nič zares ne deluje narobe,
samo program se počasi zažira v RAM.

Za preprečitev memory leakov je potrebno zagotoviti, da vsak alociran spomin,
natanko enkrat izbrišemo, oz. povedano na kratko "vsak ``new`` ima svoj
``delete``". To ne pomeni, da moramo v kodi imeti enako število besedic ``new``
in ``delete`` ampak da morajo biti poparčkani pomensko.

C++ ima nekaj mehanizmov, da se memory leakom izognemo v širokem loku: najlažje
tako, da sploh ne uporabljamo dinamičnih alokacij direktno, ampak pustimo
standardni knjižnici, v katere pravilnost zaupamo, da to počne namesto nas.

Enostaven primer memory leaka je, da preprosto ne pokličemo ``delete`` v kakšnem
od zgodnjih primerov. Poglejmo si zanimivejši primer:

.. code-block:: cpp

  int main() {
      double* d = new double(3.4);
      // uporabljamo d
      d = new double(2.7);
      // uporabljamo d
      delete d;

      return 0;
  }

Čeprav smo uporabljali samo ``d`` in ga na koncu tudi zbrisali je spomin,
pridobljen s prvim klicem ``new`` izgubljen, saj smo njegov naslov, ki je bil
shranjen v ``p`` povozili z drugo vrednostjo. Po tem tudi če bi želeli, ne
moremo več sprostiti tega spomina, saj nimamo nobenega načina, da do njega
pridemo. Zaradi tega se je v C programiranju razvil koncept "lastništva
pointerja", kjer se razmišlja o tem kdo je lastnik nekega pointerja, tj., kdo je
odgovoren za njegov izbris, kar postane pomembno predvsem v bolj kompliciranih
programih, kjer pointerje hranimo dlje časa in jih podajamo več funkcijam.


Tabele
------

V tem razdelku si bomo ogledali ročno alociranje tabel, ki se v modernem
C++ uporablja redko, toda spodobi se, da to pozna vsak C++ programer.
Če potrebujemo tabelo uporabimo ``vector`` in C++ poskrbi za nas.

Podobno kot lahko od sistema zahtevamo spomin za eno samo spremenljivko, lahko
zahtevamo od sistema tudi spomin za cel seznam teh spremenljivk.
Za to imamo na voljo operator, ki se imenuje ``new[]``, uporabimo pa ga kot

.. code-block:: cpp

  double* t = new double[25];

kar alocira prostor za 25 decimalnih števil in vrne naslov prvega elementa.
Če alokacija ne uspe (ker nam je npr. zmanjkalo spomina),
``new[]``, enako kot pri verziji brez ``[]`` vrže izjemo.

Prostor za 25 števil lahko gledamo kot tabelo. Ker ``t`` kaže na prvi element
ga lahko nastavimo z ``*t = 3.14``. Sedaj se seveda porodi naravno vprašanje,
kako nastavimo ostale elemente. Izkaže se, da lahko s pointerji računamo, podobno
kot z navadnimi števili. Naj bosta ``p`` in ``q`` neka kazalca enakega tipa in
``a`` celo število. Izračunamo lahko ``p+a``, ``p-a``, ``q-p``, poleg tega pa
lahko tudi primerjamo ``p < q`` (in ostale relacije). Naredimo lahko tudi
``++p`` in ``--p`` (in postfiksni verziji) in tudi ``p += a`` ipd.

Izraz oblike ``p+a`` poveča ``p`` za ``a`` mest. Če ``p`` kaže na naslov ``1654``
potem ``p+3`` ne kaže nujno na naslov ``1657``, ampak je to odvisno od tipa, na
katerega ``p`` kaže. Če je ``p`` tipa ``double*``, potem se ``p`` poveča za
``3*sizeof(double)``, tako da preskočimo za 3 cela decimalna števila naprej,
kar ima več smisla, kot da bi skočili za 3 bajte in končali na sredini nekega
števila. Odštevanje števila deluje podobno, razlika med dvema kazalcema pa
pove, koliko sta narazen, merjeno v velikosti tipa na katerega kažeta.
Velja seveda ``(p+a) - p == a``.

Seštevanje in odštevanje kazalcev je zelo uporabno pri delu s tabelami. Če
``t`` kot zgoraj kaže na začetek tabele, potem ``t+1`` kaže na naslednji
element, ``t+2`` na tretjega in v splošnem ``t+i`` na element na indeksu ``i``.
Če želimo na ``i``-to mesto nekaj napisati, to storimo tako, da izvedemo
``*(t+i) = -2.34``. Ker se izrazi oblike ``*(t+i)`` v C++ tako pogosto
pojavljajo, so zanje naredili poseben operator: znani operator ``[]``
za indeksiranje tabel. Po definiciji velja ``t[i] == *(t+i)``.
Ta operator nam omogoča da s tabelo ``t`` delamo kot ponavadi:

.. code-block:: cpp

  for (int i = 0; i < 25; ++i) {
      t[i] = i*i;
  }

Pri tem moramo paziti da ne gremo prek začetka ali konca tabele. C++ sam se
glede tega ne bo nič pritožil, pa tudi pri izvajanju ne pride nujno do napake --
če gremo preveč preko konca se bo program najbrž sesul s ``segmentation fault``,
toda če gremo samo malo čez tabelo, pa ne. Toda, po standardu je dostop do
elementov, ki niso del tabele *nedefinirano obnašanje* (undefined behaviour),
kar pomeni, da nimate nobene garancije kaj se bo zgodilo in se na tako obnašanje
ne morete zanašati: program se lahko sesuje, lahko dobite vrednost 0, lahko
dobite neko navidez naključno številko, lahko se pokvari nek drug del
programa...

Po koncu uporabe moramo tabelo tudi izbrisati z

.. code-block:: cpp

  delete[] t;



Kako naredimo tabelo, ki se sama povečuje
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
TODO opis.

.. code-block:: cpp

  #include <iostream>
  #include <vector>
  #include <string>

  // Dve strategiji povečevanja
  struct MultiplyByConstantAllocationStrategy {
      static int init_capacity() { return 10; }
      static int change_capacity(int capacity) {
          return static_cast<int>(capacity * 1.2);
      }
  };

  struct AddConstantAllocationStrategy {
      static int init_capacity() { return 10; }
      static int change_capacity(int capacity) {
          return static_cast<int>(capacity + 100000);
      }
  };

  // Lastna tabela
  template <typename T, typename AllocationStrategy=MultiplyByConstantAllocationStrategy>
  class Tabela {
      int size_;
      int capacity_;
      T* t;
    public:
      Tabela() : size_(0), capacity_(AllocationStrategy::init_capacity()),
             t(new T[capacity_]) {}
      // copy constructor (za kopiranje tabele)
      Tabela(const Tabela& v) : size_(v.size_), capacity_(v.capacity_) {
          t = new T[capacity_];
          for (int i = 0; i < size_; ++i) {
              t[i] = v[i];
          }
      }
      // copy assignment (za kopiranje tabele)
      Tabela& operator=(const Tabela& v) {
          size_ = v.size_;
          capacity_ = v.capacity_;
          delete[] t;
          t = new T[capacity_];
          for (int i = 0; i < size_; ++i) {
              t[i] = v[i];
          }
          return *this;
      }
      ~Tabela() { delete[] t; }
      const T& operator[](int i) const { return t[i]; }
      T& operator[](int i) { return t[i]; }
      void push_back(const T& v) {
          if (size_ == capacity_) {
              capacity_ = AllocationStrategy::change_capacity(capacity_);
              T* nt = new T[capacity_];
              for (int i = 0; i < size_; ++i) {
                  nt[i] = t[i];  // skopiramo elemente
              }
              delete[] t;
              t = nt;
          }
          t[size_++] = v;
      }
      int size() const { return size_; }
  };

  // Dodamo možnost printanja tabele.
  template <typename T>
  std::ostream& operator<<(std::ostream& os, const Tabela<T>& v) {
      if (v.size() == 0) {
          return os << "[]";
      }
      os << "[" << v[0];
      for (int i = 1; i < v.size(); ++i) {
          os << ", " << v[i];
      }
      return os << "]";
  }

  using namespace std;

  int main() {
      /* test tabele */
      Tabela<Tabela<char>> a;
      int s = 30;
      for (int i = 0; i < s; ++i) {
          a.push_back({});
          for (int j = 0; j < s; ++j) {
              a[i].push_back('a'+(i*j % 26));
          }
      }

      // cout << a << endl;

      int N = 10000;
      int n = 10000;

      {
          Tabela<int, MultiplyByConstantAllocationStrategy> t;
          for (int i = 0; i < N; ++i) {
              clock_t begin = clock();
              for (int j = 0; j < n; ++j) {
                  t.push_back(i);
              }
              clock_t end = clock();
              double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
              cout << elapsed_secs << ' ';
          }
          cout << endl;
      }

      {
          Tabela<int, AddConstantAllocationStrategy> t;
          for (int i = 0; i < N; ++i) {
              clock_t begin = clock();
              for (int j = 0; j < n; ++j) {
                  t.push_back(i);
              }
              clock_t end = clock();
              double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
              cout << elapsed_secs << ' ';
          }
          cout << endl;
      }

      {
          vector<int> t;
          for (int i = 0; i < N; ++i) {
              clock_t begin = clock();
              for (int j = 0; j < n; ++j) {
                  t.push_back(i);
              }
              clock_t end = clock();
              double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
              cout << elapsed_secs << ' ';
          }
          cout << endl;
      }


      return 0;
  }

Pametni kazalci in reference
----------------------------

C++ ima od verzije 11 v knjižnici memory




.. vim: spell spelllang=sl
