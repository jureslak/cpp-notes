Objekti
-------

Razrede v C++ uporabljamo enako kot v Pythonu. Z njimi definiramo nove
podatkovne tipe, ki ustrezajo našim potrebam. Najprej terminologija:

*Razred* je definicija našega novega tipa.  Spremenljivka tega tipa, ki jo
naredimo, se imenuje *objekt* tega razreda ali *instanca* tega razreda. *Tip* in
*razred* se nanašata na abstraktno definicijo, *objekt* ali *instanca* pa na
konkretno spremenljivko.  Funkcije, ki so vsebovane v tem objektu se imenujejo
*metode*, spremenljivke tega objekta pa *atributi*. Običajno razrede označujemo
z *PascalCase* začetnicami.

Definicija novega razreda gre v C++ tako:


.. code-block:: cpp

  class ImeTipa {
    public:
      tip1 member1;
      tip2 member2;
    private:
      tip3 member3;
      tip4 member4;
  };

.. warning::

  Na koncu definicije razreda mora biti podpičje. Če ga pozabite, lahko pride
  do zelo neprijetnih in težko razumljivih napak.

Naredimo primer razreda *Pravokotnik* in nastavimo njegove člane.
Spremenljivke našega tipa (v tem primeru Pravokotnik) definiramo enako kot vse ostale, najprej povemo tip,
nato pa ime. Kot pri funkcijah tudi razrede definiramo izven funkcije ``main``
preden jih želimo uporabljati. Kot v veliko drugih jezikih tudi v c++ do
atributov in metod dostopamo s piko ``a.x``.

.. code-block:: cpp

  class Pravokotnik {
    public:
      double a, b;
  };

  int main() {
      Pravokotnik p;
      p.a = 4;
      p.b = 1.2;
  }

Metode
~~~~~~

Dodajmo razredu metodo, ki izračuna ploščino, in še eno, ki nastavi obe
stranici. Metode so po sintaksi popolnoma enake funkcijam in do atributov
razreda imajo prost dostop (ni potrebno pisati npr. ``self.x``).

.. code-block:: cpp

  class Pravokotnik {
    public:
      void set_sides(double x, double y) {
          a = x;
          b = y;
      }
      double area() {
          return a * b;
      }
    private:
      double a, b;
  };
  int main() {
      Pravokotnik p{4, 1.2};
      p.set_sides(1, 1);
      cout << p.area() << endl;
  }  // prints 1

Private, public, protected
~~~~~~~~~~~~~~~~~~~~~~~~~~~

To so trije tipi scopa, "vidnosti" v razredih. Do public funkcij in spremenljivk
lahko dostopajo vsi, izven in znotraj razreda, do privatnih pa samo znotraj
razreda. Protected se uporablja pri dedovanju, in ga bomo spoznali kasneje.

Pogost vzorec v programiranju je, da so atributi private, spreminja in bere pa se jih
lahko samo preko public metod, saj s tem uporabniku preprečimo nekontroliran
dostop, ki bi lahko ogrozil smiselnost podatkov.

.. code-block:: cpp

  class Pravokotnik {
    public:
      void set_sides(double x, double y) {
          a = x;
          b = y;
      }
      double area() {
          return a * b;
      }
    private:
      double a, b;
  };
  int main() {
      Pravokotnik p;
      p.set_sides(1, 1);
      cout << p.area() << endl;
      p.a = 8;
  }

Zgornja koda nam vrne napako, dostopamo namreč do privatne spremenljivke `a`.

::

  a.cpp: In function ‘int main()’:
  a.cpp:14:14: error: ‘double Pravokotnik::a’ is private
         double a, b;
                ^
  a.cpp:20:9: error: within this context
         p.a = 8;
           ^

Če problematično vrstico zakomentiramo, je vse ok, saj sta ``set_sides`` in
``area`` public metodi, ki pa znotraj razreda lahko dostopata do privatnih
spremenljivk.

Seveda je najlažje programirati, če vse naredimo kar public, vendar to ni nujno
najboljša ideja. Pravzaprav je bolje, da vse naredimo privatno, in navzven
pokažemo samo nekaj metod za delo z našim razredom, saj tako uporabniku našega
razreda (torej tudi samemu sebi) preprečimo, da bi počeli kakšne neumnosti,
spravili razred v neveljavno stanje, klicali funkcije, ki so zgolj del
implementacije in se lahko spremenijo. Imeti stvari po defaultu private
spodbuja boljši design kode: če je nekaj samo implementacijski detajl, potem je
gotovo zasebno. Predstavljajte si, da bi imeli na voljo tudi vse interne
metode, ki jih razred ``vector`` uporablja za alokacijo spomina, prepisovanje
elementov, ipd. To je nepotrebno, saj ne veste kaj klicanje takih metod naredi,
poleg tega pa se lahko te metode kadarkoli zamenjajo. Toda, ker so v privatne,
bo vsa koda, ki ``vector`` uporablja, še vedno delovala (saj so bile metode
privatne in jih nismo mogli uporabljati). Tako lahko rečemo, da public metode
pravzaprav definirajo, kaj objekt je in kaj z njim lahko počnemo, pa tudi
spodobi se, da vsaka public metoda pusti objekt v veljavnem stanju (kar ni
nujno res za privatne metode). Primer: za public metode se ponavadi ne spodobi,
da bi postavljali zahteve v stilu "Če želite poklicati x, morate najprej poklicati y.",
medtem ko je za privatne to običajno.

.. _constructors:

Konstruktorji in destruktorji
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kaj pa, če želimo našemu objektu dati določene parametre že na začetku, ko ga
ustvarimo? V tem primeru definiramo *konstruktor*, to je posebna metoda, ki
omogoča ustvarjanje razreda.

Sintaksa je sledeča:

.. code-block:: cpp

  class ImeTipa {
    public: // konstruktor
      ImeTipa(tip1 member1_, tip2 member2_) : member1(member1_), member2(member2_) {
         // koda
      }
    private:
      tip1 member1;
      tip2 member2;
  };

Konstruktor naredimo tako, da napišemo ime tipa, in kot običajni funkciji
naštejemo argumente. Ponavadi želimo vsakemu članu razreda določiti vrednost,
zato parametre imenujemo kar po članih razreda (z dodanim podčrtajem, saj
enakih imen ne smemo uporabiti). Parametre lahko poimenujete seveda kakor
želite, a to je najbolj sugestivno in standardno. Sledi dvopičje in seznam
(class initializer list) članov, ki jim določimo vrednosti (kot bomo videli
kasneje, kličemo njihove konstruktorje). Nato sledi telo, ki je kot vsako telo
funkcije, in notri lahko počnemo običajne stvari. Ko smo znotraj telesa, so
spremenljivke, ki smo jih nastavili v initializer list že nastavljene, in jih
lahko uporabljamo.

Konstruktor pokličemo z oklepaji za imenom spremenljivke ``ImeTipa
ime_spremenljivke(arg1, arg2)``

Poglejmo si primer za pravokotnik.

.. code-block:: cpp

  class Pravokotnik {
    public:
      Pravokotnik(double a_, double b_) : a(a_), b(b_) {}
      void set_sides(double x, double y) {
          a = x;
          b = y;
      }
      double area() {
          return a * b;
      }
    private:
      double a, b;
  };
  int main() {
      Pravokotnik p(1, 1);
      cout << p.area() << endl;
  }  // prints 1

Vrednosti a in b smo nastavili že v konstruktorju, zato klic funkcije
``set_values`` ni bil potreben.

Razred ima lahko več kot en konstruktor. Naredimo še dva.

.. code-block:: cpp

  class Pravokotnik {
    public:
      Pravokotnik() : a(0), b(0) {}
      Pravokotnik(double a_) : a(a_) {}
      Pravokotnik(double a_, double b_) {
           a = a_;
           b = b_;
      }
    private:
      double a, b;
  };
  int main() {
      Pravokotnik p;
      Pravokotnik q(1);
      Pravokotnik r(1, 3);
      p = 1;
      r = {3, 5};
  }  // prints 1

Dodali smo *default konstruktor*, ki ne sprejme parametrov. Ta se pokliče ko
spremenljivko samo deklariramo, ``Pravokotnik p;``. Imamo še konstruktor iz ene
spremenljivke, ki nastavi obe stranici na enako vrednost. Že znan konstruktor,
pa smo prepisali na ekvivalenten, a manj običajen način, ki pa je morda
začetnikom bolj jasen in morda bolj ilustrira intuicijo. V resnici je pristop z
initializer listom tudi idejno pravi, saj tak pokličemo konstruktorje naših
članov, na enak način kot smo poklicali konstruktor našega Pravkokotnika.
Zadnji dve vrstici main funkcije kažeta sintakso z =, ki jo compiler tudi
prevede v klic konstruktorja. V prvem primeru se pokliče drugi, v drugem pa
tretji konstruktor.

Const metode in spremenljivke
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Spoznali smo že konstantne spremenljivke in reference pri klicih funkcij. Na
hitro ponovimo -- konstantne spremenljivke so tiste, ki jih ne moremo
spreminjati, niti direktno niti s klicanjem funkcij, ki bi jih spremenile.

.. code-block:: cpp

  const int a = 7;
  a = 9;   // napaka
  int b = 0;
  swap(a, b); // napaka

Kaj pa, če je naša konstantna spremenljivka objekt?

.. code-block:: cpp

  const Pravokotnik p(1, 3);
  std::cout << p.area() << std::endl;


Dobimo napako:

::

  a.cpp: In function ‘int main()’:
  a.cpp:29:22: error: passing ‘const Pravokotnik’ as ‘this’ argument discards qualifiers [-fpermissive]
         cout << p.area() << endl;
                        ^
  a.cpp:18:14: note:   in call to ‘double Pravokotnik::area()’
         double area() {

Malo kriptična napaka, pomeni, da ta funkcija "discards qualifiers", torej ne
spoštuje "dodatkov k tipu", v tem primeru je to besedica ``const``. Po domače,
funkcija lahko spreminja objekt, zato je ne smeš klicati na konstantnem
objektu.

*Ampak saj ga ne!*

Hja, ampak kako naj ubogi g++ to ve? To se reši tako, da mu poveš, da ta funckija objekta ne spreminja.
Če bi kodo prevedli s ``clang``-om, bi ta bolj prijazno rekel:

::

  a.cpp:29:15: error: member function 'area' not viable: 'this' argument has type 'const Pravokotnik', but function is not marked const
        cout << p.area() << endl;
                ^
  a.cpp:18:14: note: 'area' declared here
        double area() {

Torej, metodi moramo dodati const, ki pomeni, da ta metoda objekta, nad katerim
je definirana, ne spreminja. Ponavadi so to metode, ki ga zračunajo, izpišejo, vrnejo.
Dobra navada je, da metode, ki so ``const``, označimo s ``const``, saj imamo
sicer lahko probleme, npr, ko objekt podamo preko const ``Pravokotnik&``.
Jasno, ``const`` metode, lahko kličejo samo druge ``const`` metode, neconst
metode, pa lahko kličejo tako ``const`` kot neconst metode.
Pravilnejša definicija pravokotnika:

.. code-block:: cpp

  class Pravokotnik {
    public:
      Pravokotnik() : a(0), b(0) {}
      Pravokotnik(double a_) : a(a_) {}
      Pravokotnik(double a_, double b_) : a(a_), b(b_) {}
      void set_sides(double x, double y) {
          a = x;
          b = y;
      }
      double area() const {  // this method is const
          return a * b;
      }
    private:
      double a, b;
  };
  int main() {
      const Pravokotnik p(1, 1);
      cout << p.area() << endl;
  }  // prints 1, vse ok

Jasno metode ``set_sides`` nismo označili s ``const``, saj spremenljivke
nastavi in spremeni objekt, pa tudi compiler bi se pritožil, če bi jo, kajti
znotraj kličemo funkcijo ``operator =``, ki jasno ni ``const``, kar je bi bilo
dovoljeno.

Če torej sedaj naredimo funkcijo, ki preveri, ali je pravokotnik ploščine 1, ne
bo imela težav:

.. code-block:: cpp

  bool je_kvadrat(const Pravokotnik& p) {
      return p.area() == 1.0;
  }

.. note::

  S const lahko označimo samo metode, za navadne funkcije to nima smisla, saj
  nimajo objekta pod seboj, ki bi ga lahko spreminjale. To, ali spreminjajo
  parametre ali ne, lahko določimo že s tem, da parametrom predpišemo const ali
  ne.

Static metode in spremenljivke
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Statične so metode, ki za svoje delovanje ne potrebujejo objekta in ne dostopajo
do nobenih (ne statičnih) spremenljivk ali metod razreda. Pravzaprav je to
navadna funkcija, ki je zaradi logične strukture premaknjena znotraj razreda. V
konkretnem primeru, statična funkcija bi bila taka, ki ji je vseeno, kateri
konkreten pravokotnik ima, in lahko operira le z nečem, kar je skupno vsem
pravokotnikom. Podobno velja za statične spremenljivke, to so spremenljivke, ki
so neodvisne od konkretne instance, in so lastne classu.

Malo neumen primer:

.. code-block:: cpp

  class Pravokotnik {
    public:
      static const int number_of_sides = 2;
      static int instance_count;

      Pravokotnik() : a(0), b(0) { instance_count++; }
      Pravokotnik(double a_) : a(a_) { instance_count++; }
      Pravokotnik(double a_, double b_) : a(a_), b(b_) { instance_count++; }

      static void print_number_of_sides() {
          cout << number_of_sides << endl;
      }
      ...
  };
  int Pravokotnik::instance_count = 0;
  int main() {
      int sides = Pravokotnik::number_of_sides;  // lahko samo preko imena razreda
      Pravokotnik p;
      sides = p.number_of_sides;  // lahko pa tudi tako
      Pravokotnik::print_number_of_sides();
      Pravokotnik q(1);
      q.print_number_of_sides();  // enako velja za funkcije
      cout << q.instance_count << endl;
  }  // print 2

Kot vidimo lahko kličemo statične metode samo preko imena tipa, ne potrebujemo
objekta spodaj, nič pa ni narobe, če ga imamo. Spremenljivka instance_count, ki
jo povečamo v vsakem konstruktorju, je prav tako neodvisna od instance in je na
koncu enaka 2.

Od vsega so po mojem mnenju najpogosteje uporabljene statične konstante in
funkcije, ostalo pa bolj po redko. Statične spremenljivke imajo podobno uporabo
tudi znotraj funkcij (ob dvojni inicilizaciji se ne ponastavijo). A o tem morda
kasneje.

Copy in move konstruktorji
~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO

.. vim: spell spelllang=sl
