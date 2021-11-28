.. _podatkovnitipi:

Podatkovni tipi
===============

Podatkovni tipi so zelo pomemben koncept v C++-u. Vsaka spremenljivka ima svoj
tip in ena najpogostejših napak pri compilanju je, da se tipi ne ujemajo. Morda
je potrebno nekaj truda, da se na tipe navadimo, ampak pri velikih projektih
lahko tipi zelo pomagajo pri jasnosti kode in pri boljšem razumevanju kaj
počnemo, saj ne moremo npr. ponesreči podati funkciji napačnih parametrov.

Uvod
----

Tipe delimo na primitivne in neprimitivne. Neprimitivni so tipi, ki so
definirani kot razredi, vendar ta razlika nima posebnega vpliva. Primitivni so
vsi številski in logični tipi.

Števila
------------

Številski tipi se razlikujejo glede na to ali predstavljajo cela ali decimalna
števila in po velikosti. Celoštevilski tipi so ``short``, ``int``, ``long`` in
``long long``, decimalni pa ``float``, ``double`` in ``long double``. Med
celoštevilske tipe lahko štejemo tudi ``char``, ki predstavlja en znak, a je v
resnici številka (koda znaka v ASCII tabeli). Tipi podpirajo standardne aritmetične in bitne operacije.
Primer:

.. code-block:: cpp

  int a = 9;
  char c = 'a';
  short b = a + c + '1'; // b = 155
  double g = -12.44;
  float r = 1.1e15;

Omejitve
~~~~~~~~

============ =============== ============================
ime          velikost [#f1]_  približen razpon
============ =============== ============================
char         8 bit           :math:`\pm 127`
short        16 bit          :math:`\pm 32\,767`
int          32 bit          :math:`\pm 2.14 \cdot 10^9`
long         native
long long    64 bit          :math:`\pm 9.22 \cdot 10^{19}`
float        32 bit          :math:`\pm 3.4 \cdot 10^{\pm 38}`, 7 decimalk
double       64 bit          :math:`\pm 3.4 \cdot 10^{\pm 308}`, 15 decimalk
long double  80 bit          :math:`\pm 1.1 \cdot 10^{\pm 4932}`, 18 decimalk
============ =============== ============================

.. [#f1] Velikost je odvisna od operacijskega sistema in računalnika. Native
  pomeni ponavadi 64 ali 32 biten, zopet odvisno od računalnika. V tabeli so naštete
  najbolj pogoste velikosi. ``unsigned`` verzije imajo enak razpon, samo da je
  cel na pozitivnem delu osi. Več `tukaj
  <http://en.cppreference.com/w/cpp/language/types#Properties>`__.

Mnogo bolj podrobno in pravilno tabelo najdete `tukaj
<http://en.cppreference.com/w/cpp/language/types#Range_of_values>`__.

Naj vas to ne prestraši, pametno je poznati omejitve, a mi bomo ponavadi za
cela števila uporabljali kar ``int`` in za decimalna ``double``. (Float je
precej nenatančen, kar je na tekmovanjih, ali pa za kakšne resne izračune
problematično. Je pa lahko npr. uporabno v računalniški grafiki, kjer je
na koncu pomembna le natančnost na en piksel.
Pred celoštevilske tipe lahko vtaknemo tudi ``unsigned``, ki razpon
števila premakne na pozitivno os. Če število povečamo čez razsežnost tipa, se
ne zgodi na videz nič, številka se samo navije okrog spodnje meje. Torej, če
rečemo ``char a = 130;`` bo ``a`` v resnici enak ``-126``.

Decimalna števila zaokrožujejo in zaradi tega se pojavljajo napake. Obstaja
zelo močna veja matematike, ki se ukvarja s preučevanjem in odpravljanjem teh
napak, ampak za nas bo dovolj, da se samo zavedamo, da obstajajo. Če na primer
10 krat seštejete 0.1, to ni nujno enako celemu številu 1 (``if`` stavek se
lahko recimo ne izvede, če je kaj takega v pogoju). Dveh decimalnih števil
nikoli ni pametno direktno preverjati, ali sta enaki, ponavadi se za mero
enakosti vzame kaj podobnega kot ``abs(a - b) < -1e9``. Decimalna števila imajo
omejitve tudi glede tega, kako blizu 0 lahko pridejo (vsa lahko predstavijo
točno 0). Podobne omejitve za decimalna števila veljajo tudi v Pythonu in
ostalih programskih jezikih.

Pretvorbe
~~~~~~~~~
Med tipi lahko med pretvarjamo, poznamo implicitne in eksplicitne pretvorbe.
Compiler bo avtomatsko naredil pretvorbe, ki ne škodujejo "kvaliteti" tipa, pri
pretvorbi iz npr. ``double`` v ``int`` pa bo posvaril vsaj z opozorilom. Tako
pretvorbo lahko sami naredimo na več načinov (ki so glede na rezultat ekvivalentni):

.. code-block:: cpp

  int a = static_cast<int>(12.34);
  int b = int(12.34);
  int c = (int) 12.34;

Če uporabimo ``static_cast``, to dovoljuje prevajalniku, da preveri, da ne
počnemo česa preveč nepravilnega. Ostale pretvorbe te varnosti nimajo.

Logične vrednosti
-----------------

Logični vrednosti sta ``true`` in ``false``. Z logičnimi vrednostmi lahko
računamo kot vedno, z operatorji ``&&``, ``||`` in ``!``. Kot številski
vrednosti predstavljata 0 in 1. Logične spremenljivke imajo tip ``bool``.
Vrsti red operatorjev je enak kot v matematiki, a je priporočljivo uporabljati
oklepaje. Primer:

.. code-block:: cpp

  bool a = false;
  bool c = 4 < 2.3;
  bool m = a && c || !c;

Seznami
-------

V C++u imamo tri vrste sezamov, ki so podobni Pythonovim, eni so stari C
seznami, in dvoji novi C++ seznami. Starih C seznamov ne bomo uporabljali, ker
imajo novejši C++ seznami boljšo funkcionalnost in primerljivo hitrost.
C++ seznami se delijo na sezname fiksne dolžine in sezname spremenljive
dolžine. Seznamu fiksne dolžine moramo že na začetku povedati, kako dolg je, in
to je nespremenljivo, zaradi česar so tudi hitrejši. Seznami spremenljive
dolžine zelo podobni Pythonovim in mi jih bomo uporabljali vedno, ko bomo
potrebovali seznam, saj so zanemarljivo počasnejši od fiksnih. Seznami fiksne
dolžine so definirani v knjižnici ``array``, spremenljive dolžine pa v knjižnici
``vector``. Za delo s seznami je treba to knjižnico seveda ``#include``-ati.

Vektor (rekli mu bomo tudi kar array, seznam, tabela) definiramo s
``vector<tip> ime;``, kjer je ``tip`` tip elementov, ki so v vektorju.
Vektorja ne mešati z matematičnim 3D vektorjem, ta vektor si predstavljajte kot
seznam, ki nima veze s puščicami iz matematike.
Vsi elementi v seznamu morajo biti istega tipa. Sedaj smo definirali prazen
seznam ``ime``. Vektor lahko naredimo še na veliko drugih načinov:

.. code-block:: cpp

  #include <vector>

  using namespace std;

  int main() {
      vector<int> a;                          // prazen
      vector<int> b({1, 2, 3, 8, -12, 44});   // naštejemo elemente
      vector<int> c(10, 4);                   // 10 štiric
      vector<int> d(b.begin()+2, b.end()-1);  // [3, 8, -12]
      return 0;
  }

Dostopanje in spreminjanje elementov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vektor podpira operator ``[]``, s katerim dostopamo in spreminjamo element na
določenem indeksu:

.. code-block:: cpp

  vector<int> b({12, 4, 7, -12, 44});
  b[1] = 3;
  cout << b[2] << ' ' << b[1] << endl;
  // izpiše 7 3

.. warning::

  Če v C++-u dostopamo do elementa čez dolžino seznama, se dogajajo čudne reči.
  Lahko se ne zagodi nič in preberemo neko vrednost, ki bo neka solata, ki je
  na naslednjem mestu v ramu, lahko pa se naš program sesuje na zanimive
  načine, npr. s sporočilom ``segmentation fault``. Ta sporočila niso tako
  prijazna in lepa kot v Pythonu, a so posledica tega, da vektor ne preverja,
  sli dostopate izven njega in poskuša to pač naresti, če posegate v spomin, ki
  ni njegov, pa sistem ubije vaš program, zato recimo ne dobite podatka o tem,
  koliko ste šli čez in v kateri vrstici kode.

.. _iteratorjiuvod:

Iteratorji
~~~~~~~~~~

Iterator je objekt, ki vsebuje podatek o svoji poziciji v neki zbirki. Na nek
način je podoben indeksu. Iteratorji so mnogo bolj uporabni kot vrednosti v
zbirki same. Poglejmo si to na primeru indeksov. V seznamu najdemo vrednost 5.
Kaj na ta vrednost pove? Nič prav dosti, ali vemo katera je naslednja, katera
je prejšnja, ali smo na začetku? Če pa poznamo *indeks* vrednosti, recimo
vrednost 5 je na mestu 2, potem na vprašanja lažje odgovorimo. Iteratorji so
torej neke vrste objekti, ki hranijo pozicijo v zbirki in lahko dostopajo do
vrednosti na tem mestu, gredo na naslednje mesto, preverijo ali smo na koncu ...
Poleg tega so po tipu različni od števil, kar omogoča manj napak, saj nas
compiler na morebitno neujemanje tipov vedno opozori.

Pomembne operacije ki jih lahko počnemo z iteratorji (ne vsemi, nekateri ne
podpirajo vsega tega) so: dobivanje vrednosti, povečevanje in zmanjševanje,
povečevanje in zmanjševanje za dano število, računanje razlike med dvema
iteratorjema (razdalje). Seveda jih lahko tudi primerjamo. Pridobivanju
vrednosti iz iteratorja se reče *dereferenciranje*.

.. code-block:: cpp

  vector<int> a({12, 4, 5, -2, 11});      // tip iteratorja po zbirki je 'zbirka::iterator'
  vector<int>::iterator it = a.begin();   // .begin() vrne iterator, ki kaže na začetek zbirke
  cout << *it << endl;                    // vrednost dobimo z operatorjem *
  ++it;                                   // povečamo za 1
  cout << *it << endl;
  it += 3;                                // povečamo za 3
  if (it + 1 == a.end()) {                // se izpiše
      cout << "konec!" << endl;           // .end() vrne iteartor, ki kaže čez konec vektorja
  }
  cout << a.end() - a.begin() << endl;    // to je zato da a.end() - a.begin() vrne dolžino


Iteratorjev ali seznamov samih se ne da izpisati, seznam lahko izpišete s for
zanko, iterator pa lahko izpišete kot številski indeks tako, da izpišete ``it -
a.begin()``.
Napaka, ki jo prevajalnik javi pri tem je podobna temu:

::

  a.cpp:8:10: error: invalid operands to binary expression
          ('ostream' (aka 'basic_ostream<char>') and 'vector<int>')
      cout << a << endl;
      ~~~~ ^  ~
  /usr/bin/../lib64/gcc/x86_64-unknown-linux-gnu/4.9.1/../../../../include/c++/4.9.1/ostream:245:7:
  note: candidate function not viable: no known conversion from
          'vector<int>' to 'int' for 1st argument
      operator<<(int __p)
      ^

To se je potrebno malo naučiti brati. Prvi vrstici povesta napako: v ``ostream``
(= output stream = ``cout``) ste poskusili zatlačiti ``vector<int>``, kar se ne da.
Ostalih 80 ``info`` napak vam pove kaj pa se v ``ostream`` da zatlačiti, npr.
``int``.

Spreminjanje vektorja
~~~~~~~~~~~~~~~~~~~~~

Tu so funkcije s katerimi lahko spreminjamo vektor. Pred vsako funkcijo piše
tip, ki ga vrača, pišejo pa tudi tipi parametrov. Funkcije so poenostavljene za
lažje razumevanje. ``T`` pomeni katerikoli tip se pač odločimo, da bo naš
vektor vseboval. ``void`` pomeni, da funkcija ne vrača ničesar.

.. cpp:class:: template <typename T> vector

  .. cpp:function:: iterator begin()

    Vrne iterator, ki kaže na prvi element vektorja.

  .. cpp:function:: iterator end()

    Vrne iterator, ki kaže čez zadnji element vektorja.

  .. cpp:function:: int size()

    Vrne velikost (dolžino) vektorja.

  .. cpp:function:: iterator insert(iterator pos, T vrednost)

    Vstavi element na mesto pred iterator ``pos`` in vrne iterator na
    novo vstavljeni element. Vsi elementi za tem se premaknejo za eno mesto
    nazaj, tako da ta operacija lahko traja dolgo.

  .. cpp:function:: iterator erase(iterator pos)

    Izbriše element, na katerega kaže ``pos``. Vektor je za en element krajši,
    vsi elementi za izbrisanim se premaknejo eno mesto naprej, tako da ta
    operacija lahko traja dolgo.

  .. cpp:function:: void push_back(T vrednost)

    Doda ``vrednost`` na konec vektorja.

  .. cpp:function:: void pop_back()

    Zbriše zadnji element iz vektorja.

Primer:

.. code-block:: cpp

  vector<int> a({1, 2, 3});                                 // [1, 2, 3]
  a.push_back(4);                                           // [1, 2, 3, 4]
  a.push_back(5);                                           // [1, 2, 3, 4, 5]
  a.pop_back();                                             // [1, 2, 3, 4]
  vector<int>::iterator it = a.insert(a.begin() + 1, 100);  // [1, 100, 2, 3, 4]
  a.erase(it + 2);                                          // [1, 100, 2, 4]
  cout << a.size() << endl;                                 // izpiše 4


Nizi znakov
-----------

V C-ju so nizi natanko seznami znakov. To je zelo bedno, zato bomo uporabljali
C++ stringe. Ti so definirani v headerju ``string``, tako da je treba za delo s
stringi napisati ``#include <string>``.

Stringi se obnašajo v C++-u kot seznami znakov, to pomeni da jih lahko
spreminjamo, brišemo in dodajamo znake, hkrati pa imajo veliko metod, namenjene
delu z njimi. Dobesedni stringi (to so dejanske besede v narekovajih (npr.
``"beseda"``) v kodi) se
interpretirajo kot stari C stringi, a se implicitno pretvorijo v C++ stringe.

.. warning::

  C++ pozna močno razliko med enojnimi in dvojnimi narekovaji: `""` označujejo
  ``string``, med tem ko `''` označujejo ``char`` (ki se lahko implicitno pretvori tudi v
  string). Napisati npr. ``'asdf'`` bo compile error, seveda pa je popolnoma
  veljavno napisati ``'\n'``, ki je v resnici število znaka za novo vrstico v
  ASCII tabeli.

Stringi so lahko sestavljeni samo iz ASCII znakov, posebne znake kot vedno
vnašamo z ``\``, npr. ``\n`` ali ``\\``.

Stringe se lahko izpiše s ``cout`` in
preber s ``cin``. Cin prebere vse do prvega whitespacea. Če želimo prebrati celo
vrstico, uporabimo funkcijo ``getline``.

.. cpp:function:: istream& geline(istream& is, string& str)

  Iz input streama ``istream`` (recimo cin) prebere eno vrstico in jo shrani v niz ``str``.

.. cpp:class:: string

  .. cpp:function:: int length()

    Vrne dolžino niza.

  .. cpp:function:: insert(int pos, string niz)

    Vstavi ``niz`` pred pozicijo ``pos``.

  .. cpp:function:: int find(string niz)

    Vrne indeks, kjer se začne ``podniz`` oz ``str::npos``, če ``podniz`` ne
    obstaja.

  .. cpp:function:: string substr(int pos1 = 0, int pos2 = string::npos)

    Vrne podniz od ``pos1`` do ``pos2``.

String ima res veliko metod, popolno dokumentacijo najdete `tukaj
<http://www.cplusplus.com/reference/string/string/>`__.

Primer:

.. code-block:: cpp

  string a = "Danes je lep dan in Janezu se kot vedno ne da v sluzbo".
  cout << a << endl;
  int indeks = a.find("da");
  if (indeks != string::npos) {
      string konec = a.substr(indeks);
      cout << kones.length() << endl;
  }

Množice
-------

Množice so podobne matematičnim množicam, elementi so različni in unikatni.
Posebnost v C++-u je, da so elementi tudi vedno sortirani. Množice ne podpirajo
dostopa pri danem indeksu, podpirajo pa hitro preverjanje ali je nek element v
množic ter hitro dodajanje in brisanje glede na vrednost. Množice so tako kot
seznami iterabilne (seveda z iteratorji, saj ne moremo narediti ``set[x]``)

Množice so definirane v headerju ``set``, tako da je treba za delo z množicami
na začetek datoteke dodati ``#include <set>``. Kot pri vektorju je tip množice
``set<T>``, kjer je ``T`` izbrani tip, ki definira operator ``<``.

.. cpp:class:: template <typename T> set

  .. cpp:function:: int size()

    Vrne velikost množice.

  .. cpp:function:: iterator insert(T vrednost)

    Vstavi vrednost ``vrednost`` v množico, če ta še ne obstaja. Vrne iterator
    na vstavljeno vrednost.

  .. cpp:function:: int erase(T vrednost)

    Odstrani vrednost ``vrednost`` iz množice. Če vrednost ne obstaja v
    množici, se ne zgodi nič. Vrne število izbrisanih vrednosti, torej 0 ali 1.

  .. cpp::function:: int find(T vrednost)

    Vrne število elementov z vrednostjo ``vrednost`` v množici, torej 0 ali 1.

Primer:

.. code-block:: cpp

  set<int> a({1, 2, 3, 3, 2, 1});            // {1, 2, 3}
  cout << a.size() << endl;                  // 3
  a.insert(5);                               // {1, 2, 3, 5}
  a.erase(3);                                // {1, 2, 5}
  if (a.find(1)) {                           // true
      cout << "1 is in the set" << endl;     // se izpiše
  }
  cout << "Vsebina:" << endl;
  for (set<int>::iterator it = a.begin(); it != a.end(); ++it) {
      cout << *it << endl;                   // {1, 2, 5}
  }

Obstaja tudi ponavadi hitrejša in neurejena verzija množic z enakimi
metodami, ki se imenuje ``unordered_set``.


Asociativni seznami
-------------------

To je struktura podobna Pythonovim slovarjem (v bistvu še bolj ``deafultdict``),
a je kot vse ostale podatkovne strukture homogena. Podatke, vrednosti, ki so
enega tipa, imamo shranjene pod ključi, ki so nekega drugega tipa. Ta dva tipa
bomo klicali ``K`` in ``V``.  Asociativni seznami (mapi), so definirani v
headerju ``map`` in za njihovo uporabo moramo na začetek napisati ``#include
<map>``. Ključi so enolični, vrednosti se pri novem ključu ustvarijo
avtomatično. V resnici so vrednosti v mapu pari, kar pomeni, da lahko do
ključev in vrednosti dostopamo kot do prvega in do drugega elementa para.

Pari
~~~~

C++ definira pare, to so objekt, ki lahko držijo dva različna tipa.
Definira se jih s kot ``pair<A, B> par;``, kjer sta ``A`` in ``B`` tipa
elementov v paru. Do elementov dostopamo z atributoma ``.first`` in
``.second``. Par lahko tudi naredimo s funkcijo ``make_pair``.

.. code-block:: cpp

  pair<int, string> par = make_pair(12, "asdfasdf");  // lahko tudi = {12, "asdfasdf"}
  cout << "(" << par.first << ", " << par.second << ")\n";

Uporaba asociativnih seznamov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Mapi podpirajo dodajanje in dostopanje do elementov z uporabo operatorja
``[]``.

.. cpp:class:: template <typename K, typename V> map

  .. cpp:function:: int size()

    Vrne število elementov v mapu.

  .. cpp:function:: int erase(K kljuc)

    Zbriše element s ključem ``ključ``, če obstaja in vrne število izbrisanih
    argumentov.

  .. cpp:function:: int find(K kljuc)

    Vrne število elementov s ključem ``kljuc``, torej 0 ali 1.

Primer uporabe:

.. code-block:: cpp

  map<char, int> counter;
  string znaki = "abeceda";
  for (int i = 0; i < znaki.length(); ++i) {
      counter[znaki[i]]++;    // pri danem znaku povečamo count
  }
  for (map<char, int>::iterator it = counter.begin(); it != counter.end(); ++it) {
    cout << it->first << " => " << it->second  << endl;
  }
  // Izpis:
  // a => 2
  // b => 1
  // c => 1
  // d => 1
  // e => 2

Tukaj bi morali po vseh pravilih do sedaj napisati ``(*it).first`` (torej,
najprej dobimo vrednost, in potem dobimo ``first`` te vrednosti, toda C++ to
poenostavi in definira operator ``x->y``, ki pomeni natanko ``(*x).y``.

Dodatek o vseh zbirkah
----------------------

C++-ove podatkovne strukture pokrivajo veliko širše področje kot opisano tukaj,
obstajajo še strukture ``deque``, ``queue``, ``priority_queue``, ``stack``,
``bitset``, ``multiset``, ``multimap``, ``list``, ki imajo druge prednosti in
namene uporabe. Ko izbirate svojo strukturo, pomislite na to kaj od nje
potrebujete, kakšne operacije boste izvajali in kakšne elemente boste
shranjevali.

.. _range-for:

Range for zanka
~~~~~~~~~~~~~~~

Za vsako zbirko, ki definira ``.begin()`` in ``.end()`` iteratorja, ki
podpirata ``++it``, ``*it`` in ``!=``, se lahko uporablja ``range for`` zanko.
Vse zbirke opisane zgoraj, te metode definirajo.

Torej lahko za vektor ``v``, če nas indeksi njegovih elementov ne zanimajo, ali
pa morda naša zbirka sploh ne podpira dostopa po indeksih, namesto:

.. code-block:: cpp

  for (vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
      // počni nekaj z *it
  }

napišemo:

.. code-block:: cpp

  for (int x : v) {
      // počni nekaj z x
  }

Paziti je potrebno, da se v tem primeru ustvari kopija ``x``, in da če ``x``
spremenimo, to nima vpliva na ``v``. A je tudi to rešljivo. Zgornja verzija v
nobenem primeru ni optimalna, če vrednosti ne želimo spreminjati, napišemo

.. code-block:: cpp

  for (const int& x : v) {
      // počni nekaj z x
  }

kar prepreči kopiranje ``x``, saj je ``x`` dejanski objekt iz ``v``. Če
``const`` izpustimo, lahko ``x`` tudi spreminjamo, kar bo spremenilo tudi
elemente ``v``. Več o referencah (to so tisti & znaki) v poglavju
:ref:`funkcijecpp`. Tip ``int`` lahko nadomestimo tudi z ``auto``, da nam ni
potrebno pisati zelo dolgih tipov, pri čemer še vedno popolnoma veljavno
uporabljamo npr. ``auto& x`` z enakim pomenom kot prej.

.. vim: spell spelllang=sl
