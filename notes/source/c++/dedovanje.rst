Dedovanje
---------

Dedovanje je način, da novi tipi obdržijo (podedujejo) atribute in metode
drugih tipov. Poleg tega lahko dodajo novo obnašanje, ali spremenijo starega.
Slednji koncept se imenuje *overriding*, ki ga ne mešati z :ref:`overloading`.

Osnove dedovanja
~~~~~~~~~~~~~~~~

Začnimo s preprostim primerom:

.. code-block:: cpp

  class Torta {
    public:
      void peci() { cout << "Torta se pece." << endl; }
  };

  class RojstnodnevnaTorta : public Torta {
    public:
      int st_sveck;
      RojstnodnevnaTorta() : st_sveck(0) {}
      void dodaj_svecke(int n) { st_sveck = n; }
  };

Tukaj razred ``RojstnodnevnaTorta`` deduje od razreda ``Torta``,
saj je rojstnodnevna torta posebna vrsta torte - relacija "je"
nakazuje, da je uporaba podrazreda primerna. Po drugi strani, rojstnodnevna
torta ima svečke, kjer relacija "ima" označuje da so svečke njen atribut (in ne
npr. da bi ``RojstnodnevnaTorta`` dedovala od svečke).

Sintaksa oblike  ``class B : public A`` označuje dedovanje, pri čemer ``B``
dobi vse atribute in metode, ki jih ima ``A``. Beseda ``public`` označuje, da
atributi ohranijo enak nivo dostopa (npr. ``public``, ``private`` ali
``protected``), kot so ga imeli v ``A``.

Pri dedovanju lahko ``B`` doda
novo obnašanje in nove podatke, tako kot smo do zgoraj naredili za rojstnodnevno
torto. Pravimo, da je ``A`` *podrazred* razreda ``B``, ``B`` pa *nadrazred*
razreda ``A``.

Sedaj lahko uporabljamo v podrazredu tudi podedovane metode nadrazreda.

.. code-block:: cpp

  int main() {
      RojstnodnevnaTorta torta;
      torta.peci();  // podedovano od torte
      torta.dodaj_svecke(7);
  }


Konstruktorji in destruktorji
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Dodajmo v naše razrede še konstruktorje. Razred ``Torta`` naj ima maso, razred ``RojstnodnevnaTorta``
pa še ime slavljenca. Oglejmo si definiciji:

.. code-block:: cpp

  class Torta {
      double masa_;
    public:
      Torta(double masa) : masa_(masa) {}
      void peci() { cout << "Torta se pece." << endl; }
  };

  class RojstnodnevnaTorta : public Torta {
    public:
      string slavljenec_;
      int st_sveck;
      RojstnodnevnaTorta(const string slavljenec, double masa) :
          Torta(masa), slavljenec_(slavljenec), st_sveck(0) {}
      void dodaj_svecke(int n) { st_sveck = n; }
  };

Razred ``Torta`` ima običajen konstruktor, razred ``RojstnodnevnaTorta``
pa mora v konstruktorju kot prvo stvar poklicati nek konstruktor razreda
``Torta``, ki mu v zgornjem primeru poda maso. To se je zgodilo tudi v prejšnjem
primeru, le da ni bilo eksplicitno napisano. Razred ``Torta`` je namreč imel
default konstruktor, ki ne sprejeme parametrov in se je samodejno poklical
pred klicem konstruktorja ``RojstnodnevnaTorta``. Če imamo verigo dedovanja
``D : C : B : A`` se ob konstruiranje objekta ``D`` začne s klicem izbranega
konstruktorja ``A``, nadaljuje z ``B``, ``C``, konstruktor ``D`` pa se pokliče
zadnji, ko so vsi starši že narejeni. Med drugim to pomeni, da so podedovani deli
objekta že konstruirani in lahko npr. kličemo podedovane metode ali uporabljamo
podedovane atribute. V drugih jezikih se tak klic pogosto naredi z uporabo
``super`` (npr. Python, Java).

Pri destruktorjih je zgodba podobna, a obrnjena okrog. Če na razredu tipa ``D``
pokličemo destruktor, se po koncu avtomatsko pokličejo tudi konstruktorji
staršev, tako da so podedovani atributi od ``A`` uničeni zadnji.

Poglejmo si to še na primeru:

.. code-block:: cpp

  class A {
    public:
      A()  { cout << __func__ << endl; }
      ~A() { cout << __func__ << endl; }
  };

  class B : public A {
    public:
      B() { cout << __func__ << endl; }
      ~B() { cout << __func__ << endl; }
  };

  class C : public B {
    public:
      C() { cout << __func__ << endl; }
      ~C() { cout << __func__ << endl; }
  };

  class D : public C {
    public:
      D() { cout << __func__ << endl; }
      ~D() { cout << __func__ << endl; }
  };

  int main() {
      cout << "test konstruktorjev in destruktorjev:" << endl;
      { D d; }
      return 0;
  }

Makro ``__func__`` je poseben ukaz v C++, ki se tekom prevajanja razširi v ime funkcije, kjer
smo ga uporabili. Če poženemo zgornji program, se izpiše

::

  test konstruktorjev in destruktorjev:
  A
  B
  C
  D
  ~D
  ~C
  ~B
  ~A

kar se sklada z zgornjo razlago. Prav tako vidimo, da so vsi klici
konstruktorjev ali destruktorjev staršev avtomatski
in jih prevajalnik sam zgenerira namesto nas.

.. _slicing:

Slicing
~~~~~~~

Eno izmed osnovnih načel dedovanja je, da lahko spremenljivko bolj specifičnega
tipa shranimo kot manj specifičen tip. Z našim primerom od prej gre sklep tako:
ker je ``RojstnodnevnaTorta`` tudi ``Torta``, lahko spremenljivko tipa
``RojstnodnevnaTorta`` shranimo v spremenljivko tipa ``Torta``.

.. code-block:: cpp

  RojstnodnevnaTorta rt("Janez", 3.4);
  Torta t = rt;

Pri tem zgubimo vse informacije o tem, da je ``t`` kdaj bila
``RojstnodnevnaTorta`` in na spremenljivki ``t`` lahko kličemo le metode in
dostopamo do atributov, ki jih ima ``Torta``. Ta proces se imenuje *slicing*
ali *object slicing*, saj od podobjekta odrežemo stran vse metode in atribute,
ki jih osnovni objekt nima. To je z vidika alokacije prostora smiselno, za
spremenljivko tipa ``Torta`` imamo rezervirano toliko prostora, kot ga
potrebujemo zanjo in dodatne informacije morajo preč.

.. _hiding:

Hiding
~~~~~~

Recimo, da sedaj spremenimo definicijo razreda ``RojstnodnevnaTorta``,
tako da odstranimo dodatne konstruktorje in dodamo lastno metodo ``peci``.

.. code-block:: cpp

  class RojstnodnevnaTorta : public Torta {
    public:
      int st_sveck;
      RojstnodnevnaTorta() : Torta(1.0), st_sveck(0) {}
      void dodaj_svecke(int n) { st_sveck = n; }
      void peci() { cout << "Pecem rojstnodnevno torto." << endl; }
  };

Sedaj poglejmo, kaj se zgodi, ko pokličemo

.. code-block:: cpp

  RojstnodnevnaTorta rt;
  Torta t = rt;
  rt.peci();
  t.peci();

Izpiše se ``Pecem rojstnodnevno torto.``, čemur sledi še ``Torta se pece.``.
To je zato, ker je ``t`` tipa ``Torta``, ``rt`` pa tipa ``RojstnodnevnaTorta``
in metoda ``peci`` se na teh dveh razredih obnaša različno. v veliko programskih
jezikih, npr. v Javi, bi se obakrat izpisalo ``Pecem rojstnodnevno torto.``,
saj bi jezik se vedno vedel, da se, kljub temu, da je ``t`` tipa ``Torta``, v
njem skriva ``RojstnodnevnaTorta``. V C++ zaradi slicing-a temu ni tako.
Z zgornjim primerom smo dosegli le, da na objektu ``rt`` ne moremo več direktno
metode ``peci`` iz razreda ``Torta``, saj jo je skrila enako imenovana metoda
``peci`` iz razreda ``RojstnodnevnaTorta``.
Temu procesu se v angleščini reče *hiding*, saj metoda iz podrazreda
prepreči dedovanje (skrije) metode iz nadrazreda, ki imajo enako ime.
To bi se zgodilo tudi, če metoda
``peci`` ne bi imela popolnoma enakih parametrov, kot metoda ``peci`` iz razreda
``Torta``. Primer:

.. code-block:: cpp

  class RojstnodnevnaTorta : public Torta {
    public:
      int st_sveck;
      RojstnodnevnaTorta() : Torta(1.0), st_sveck(0) {}
      void dodaj_svecke(int n) { st_sveck = n; }
      void peci(int m) { cout << "Pecem rojstnodnevno torto za " << m << "minut." << endl; }
  };

Tudi v tem primeru prek objekta ``rt`` ne bi morali poklicati ``rt.peci()`` brez
parametrov, saj se to sklicuje na skrito (in zato ne podedovano) metodo ``peci``
iz razreda ``Torta``.  Dobimo napako:

::

  torta.cpp: In function ‘int main()’:
  torta.cpp:21:13: error: no matching function for call to ‘RojstnodnevnaTorta::peci()’
       rt.peci();
               ^
  torta.cpp:15:10: note: candidate: ‘void RojstnodnevnaTorta::peci(int)’
       void peci(int m) { cout << "Pecem rojstnodnevno torto za " << m << "minut." << endl; }
            ^~~~
  torta.cpp:15:10: note:   candidate expects 1 argument, 0 provided

ki pove le, da smo metodo ``peci`` poklicali narobe. Prevajalnik ``clang++`` je
tukaj bolj uporabniku prijazen:

::

  torta.cpp:21:8: error: too few arguments to function call, expected 1, have 0; did you mean 'Torta::peci'?
      rt.peci();
         ^~~~
         Torta::peci
  torta.cpp:6:10: note: 'Torta::peci' declared here
      void peci() { cout << "Torta se pece." << endl; }
           ^
  1 error generated.

in namigne, da smo morda želeli poklicati metodo iz nadrazreda.
Če želimo poleg metod v podrazredu tudi metode z enakim
imenom iz osnovnega razreda, moramo njihovo dedovanje eksplicitno zahtevati.
To lahko storimo z ukazom ``using``, kot v primeru spodaj.

.. code-block:: cpp

  class RojstnodnevnaTorta : public Torta {
    public:
      int st_sveck;
      RojstnodnevnaTorta() : Torta(1.0), st_sveck(0) {}
      void dodaj_svecke(int n) { st_sveck = n; }
      using Torta::peci;
      void peci(int m) { cout << "Pecem rojstnodnevno torto za " << m << "minut." << endl; }
  };

Sedaj imamo na voljo tako ``rt.peci()`` (eksplicitno podedovano iz razreda ``Torta``) in ``rt.peci(7)``
iz razreda ``RojstnodnevnaTorta``.
Če bi imeli obe metodi isto ime, ki morali (pa tudi sedaj lahko) metodo iz
nadrazreda klicati z polno kvalificiranim imenom kot ``rt.Torta::peci()``.
Zaenkrat sicer še ne vemo, kaj so virtualne
metode, toda princip skrivanja je zanje enak kot za običajne metode (kadar ne
pride v igro overriding).

.. _virtual:

Polimorfizem in virtualne funkcije
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pred branjem morate biti seznanjeni s snovjo v poglavju :ref:`pointers`.
Zaradi enostavnosti bomo v tem poglavju uporabljali navadne kazalce,
vendar vse deluje enako tudi s pametnimi kazalci.

Polimorfizem (angl. *polymorphism*) pomeni "imeti več oblik" in se v kontekstu
dedovanja nanaša na to, imamo lahko več podrazredov istega nadrazreda, ki
se obnašajo vsak na svoj način, medtem ko še vedno imajo iste metode,
predpisane s strani nadrazreda.

Denimo da imamo spodnjo situacijo:

.. code-block:: cpp

  struct Animal {
      string oglasanje() const { return ""; }
  };

  struct Dog : public Animal {
      string oglasanje() const { return "Hov"; }
  };

  struct Cat : public Animal {
      string oglasanje() const { return "Nyaa"; }
  };

  int main() {
      Cat c;
      Dog d;
      vector<Animal> v;
      v.push_back(c);
      v.push_back(d);
      for (const Animal& a : v) {
          cout << a.oglasanje() << endl;
      }
      return 0;
  }

Ko poženemo zgornji program, ki radi, da se izpiše ``Nyaa`` in ``Hov``,
saj smo v ``v`` shranili mačko in psa. Toda, kot smo se naučili v razdelku
:ref:`slicing` se objekta ``Cat`` in ``Dog`` pretvorita v ``Animal`` in
vse dodatne informacije izginejo. Izpiše se torej dvakrat prazen niz.
Toda, če uporabimo kazalce, problem z
različnimi velikostmi objektov, ko nadrazredu priredimo podrazred, izgine.
Oba objekta sta kazalca enake velikosti (kakršna pač je na tem sistemu)
in lahko kažeta na različno velika objekta. toda, to da še ni ovir, ne pomeni da
je obnašanje tako. Koda spodaj

.. code-block:: cpp

      Cat* c = new Cat();
      Dog* d = new Dog();
      vector<Animal*> v;
      v.push_back(c);
      v.push_back(d);
      for (const Animal* a : v) {
          cout << a->oglasanje() << endl;
      }
      return 0;

še vedno izpiše dva prazna niza: oba objekta sta kazalca na tip ``Animal``
in enako kot prej se pokliče metoda ``oglasanje`` na tipu ``Animal``.

To, da bi se metoda ``oglasanje`` obnašala drugače, glede na to ali je vrednost,
na katero kaže kazalec, v resnici tipa ``Cat``, stane nekaj operacij. Pri drugih
jezikih (npr. Java) se to vedno preveri in uporabnik za vsak klic plača te
operacije, filozofija C++ pa je, da uporabnik ne plača, za stvari, ki jih ni
zahteval in moramo polimorfično obnašanje posebej zahtevati.

To storimo z besedo ``virtual`` pred neko metodo. Ta označuje, da pri tej metodi
podpiramo polimorfično obnašanje in dovolimo, da jo podrazredi predefinirajo
(overridajo). Virtualne funkcije niso virtualne v smislu da ne obstajajo (te
bomo spoznali kasneje), ampak so virtualne zgolj v smislu, da deklaracija ni
direktno povezana z implementacijo. Kot bomo videli, so to funkcije, za katere
je implementirano dinamično razvrščanje (angl. *dynamic dispatch*).

Spremenimo definicijo ``Animal`` v sledečo.

.. code-block:: cpp

  struct Animal {
      virtual string oglasanje() const { return ""; }
  };

Vse kar smo dodali, je beseda ``virtual``, ki označuje, da naj se
pri klicu funkcije ``oglasanje`` uporabi polimorfizem: med izvajanjem programa
(in ne pri prevajanju, kot ponavadi), se glede na trenuten tip kazalca na
objekt izbere, katera implementacija virtualne funkcije ``oglasanje`` bo
poklicana. Izbere se tisto, ki pripada objektu, ki je dejansko shranjen
na mestu, kamor kaže kazalec. S spremenjeno definicijo, bi zadnji primer izpisal
``Nyaa`` in ``Hov``, saj je prvi objekt (čeprav shranjen kot ``Animal*``) v
resnici tipa ``Cat*`` in bi se poklicala njegova metoda ``ogasanje`` (ki
je predefinirala tisto iz ``Animal``). Enako se zgodi za drugi element.
Temu obnašanju pravimo polimorfizem in dinamičnemu klicanju glede na tip objekta
med izvajanjem *dynamic dispatch*. Enako obnašanje dobimo, če kličemo metode
prek referenc na objekte.

.. code-block:: cpp

  void oglasaj(const Animal& a) {
      cout << a.oglasanje() << endl;
  }

  int main() {
      oglasaj(Cat());
      oglasaj(Dog());
      return 0;
  }

Izpiše se ``Nyaa`` in ``Hov``, saj je klic prek reference polimorfičen.

Predefinicije virtualnih funkcij so avtomatsko virtualne, tako da ni potrebno
ponovno pred njih pisati besede ``virtual``. Da pa se izognemo morebitnim
napakam, je dobro uporabiti besedo ``override`` s katero prevajalniku (in
programerju) nakažemo, da je mišljeno, da ta funkcija predefinira neko virtualno
funkcijo iz nadrazreda. Primer, ko nam to pomaga, sledi. Denimo, da definiramo
podrazred ``Dog`` tako, pri čemer si mislimo, da smo predefinirali
``oglasanje``.

.. code-block:: cpp

  struct Dog : public Animal {
      string oglasanje() { return "Hov"; }
  };

Toda, Če bi pognali ``Animal* a = new Dog(); cout << a->oglasanje() << endl;``
bi bili najprej prijetno presenečeni, ker prevajalnik nebi javil napak,
in nato neprijetno presenečeni, ker bi se izpisal prazen niz.
To je zato, ker smo pozabili ``const`` pri zgornji metodi in je prevajalnik
to smatral kot drugo metodo, ki je samo skrila (v smislu razdelka :ref:`hiding`)
metodo ``oglasanje`` iz nadrazreda. Če pa uporabimo ``override``


.. code-block:: cpp

  struct Dog : public Animal {
      string oglasanje() override { return "Hov"; }
  };

pa nas prevajalnik posvari:

.. code-block:: none

  program.cpp:9:12: error: ‘std::__cxx11::string Dog::oglasanje()’ marked ‘override’, but does not override
       string oglasanje() override { return "Hov"; }
              ^~~~~~~~~

Prevajalnik Clang, nam celo predlaga, da smo morda mislili predefinirati metodo, ki
smo jo ponesreči skrili in celo pove, v čem se razlikujeta:

.. code-block:: none

  program.cpp:9:24: error: non-virtual member function marked 'override' hides virtual member function
      string oglasanje() override { return "Hov"; }
                         ^
  programprogram.cpp:5:20: note: hidden overloaded virtual function 'Animal::oglasanje' declared here: different qualifiers (const vs none)
      virtual string oglasanje() const { return "";}
                     ^

Podobno se zgodi, če smo ponesreči pozabili metodo v nadrazredu označiti kot
virtualno, čeprav smo popolnoma pravilno predefinirali metodo spodaj. V tem
primeru se brez ``override`` prevajalnik prav tako ne pritoži in program samo ne
deluje po naših željah, medtem ko z ``override`` dobimo jasno napako

.. code-block:: none

  program.cpp:9:30: error: only virtual member functions can be marked 'override'
      string oglasanje() const override { return "Hov"; }
                               ^~~~~~~~~

Uporaba ``override`` je tako zelo priporočena in pri prevajalnikih obstajajo
celo zastavice, ki opozorijo, da smo to besedo pozabili.

.. warning::

  Polimorfično obnašanje dobimo samo, če imamo oboje: **virtualno funkcijo**, ki smo
  jo klicali prek **kazalca** ali **reference**, ki je tipa našega nadrazreda.

  To pomeni, da tudi če je metoda virtualna, pa jo kličemo direktno na
  objektu nadrazreda, se bo klicala metoda nadrazreda, in ne od potencialnega
  otroka (zaradi slicinga). Prav tako, tudi če kličemo metodo prek kazalca,
  ki je z enakim imenom definirana v podrazredu, pa je nismo označili kot
  virtualne, se bo zopet poklicala metoda nadrazreda. To pokaže naslednji
  primer:

  .. code-block:: cpp

    struct A {
        void f() { cout << "A::f" << endl; }
        virtual void g() { cout << "A::g" << endl; }
    };

    struct B : public A {
        void f() { cout << "B::f" << endl; }
        void g() override { cout << "B::g" << endl; }
    };

    int main() {
        A a;
        B b;
        A ab = B();
        a.f(); a.g();
        b.f(); b.g();
        ab.f(); ab.g();

        cout << "------------" << endl;

        A* pa = &a;
        B* pb = &b;
        A* pab = &b;
        pa->f(); pa->g();
        pb->f(); pb->g();
        pab->f(); pab->g();

        cout << "------------" << endl;

        A& ra = a;
        B& rb = b;
        A& rab = b;
        ra.f(); ra.g();
        rb.f(); rb.g();
        rab.f(); rab.g();
    }

  Pri prvem sklopu se vedno kličejo metode (ne glede na virtualnost)
  pripadajoče tipu objekta, saj kličemo direktno prek objekta.
  Pri drugem in tretjem sklopu pa se metoda ``g`` pri klicu
  prek kazalca ali reference kliče polimorfično in tudi v zadnji vrstici dobimo
  izpis ``B::g``.

  .. code-block:: none

    A::f
    A::g
    B::f
    B::g
    A::f
    A::g
    ------------
    A::f
    A::g
    B::f
    B::g
    A::f
    B::g
    ------------
    A::f
    A::g
    B::f
    B::g
    A::f
    B::g


Stvari postanejo komplicirane, če imamo na kupu več funkcij z enakim imenom in
različnimi parametri, nekatere so virtualne, nekatere niso in lahko z
predefiniranjem neke metode uvedemo skrivanje neke druge...

Konstruktorji in virtualni destruktorji
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Osnove o konstruktorjev in destruktorjev so razložene v razdelku
:ref:`constructors`, ta razdelek opisuje njihovo obnašanje pri dedovanju.

Če razred ``B`` deduje od razreda ``A``, potem se vedno ko naredimo objekt tipa
``B`` najprej pokliče konstruktor starša, nato pa še naš konstruktor. to med
drugim pomeni, da se v konstruktorju ``B`` lahko zanašamo na obstoj in pravilno
delovanje vseh metod objekta ``A``. Tak sistem konstruiranja objektov
zagotavlja, da konstruktor ``A`` skrbi za vse, kar je v povezavi s tipom ``A``,
konstruktor ``B`` pa za vse kar je v povezavi s tipom ``B``.

Podobno velja tudi pri destruktorjih. Pri
uničenju objekta tipa ``B`` se najprej pokliče destruktor ``B``, ki kot zadnje
dejanje pokliče starševski destruktor.

Primer (z napako, razloženo kasneje):

.. code-block:: cpp

  struct A {
      A() { cout << "A ctor" << endl; }
      ~A() { cout << "A dtor" << endl; }
  };

  struct B : public A {
      B() { cout << "B ctor" << endl; }
      ~B() { cout << "B dtor" << endl; }
  };

  int main() {
      B b;
      return 0;
  }

Zgornja koda izpiše

::

  A ctor
  B ctor
  B dtor
  A dtor


Poglejmo si še, kaj se zgodi, če kličemo objekte prek pointerjev.
Funkcijo ``main`` od zgoraj spremenimo v

.. code-block:: cpp

  int main() {
      A* b = new B();
      delete b;
      return 0;
  }

in ko jo poženemo, dobimo

::

  A ctor
  B ctor
  A dtor

Kot vidimo, se destruktor ``B`` ni poklical. To pravzaprav ni nepričakovano, ker
smo ``b`` naredili kot objekt tipa ``B``, sta te poklicala oba konstruktorja,
nato smo ga shranili v kazalec tipa ``A``, ko pa smo ga uničili, se je poklical
le destruktor ``A``, saj je to bil takratni tip objekta. Toda to pomeni, da je
pol objekta (``B``-jev del) ostalo nepospravljenega. Obnašanje je podobno kot
pri virtualnih in navadnih funkcijah (glej :ref:`virtual`). Rešitev je, da se
destruktor ``B`` označi kot virtualen. Če vemo, da objekta ne bomo nikoli
uničevali prek kazalca na starševski razred, tega ni potrebno storiti, vendar se je
za vsak slučaj dobro navaditi, da pri vsakem dedovanju označimo destruktor v
spodnjem razredu kot virtualen, da se izognemo potencialnim težavam v
prihodnosti.

Ko destruktor ``B`` izgleda kot ``~B() { cout << "B dtor" << endl; }``, dobimo
pričakovan izhod

::

  A ctor
  B ctor
  B dtor
  A dtor


Povedali smo, da prevajalnik za nas pokliče starševske konstruktorje, kar drži,
če obstaja default konstruktor za starša.
Če ima starševski konstruktor parametre, ga moramo pri konstruiranju
poklicati eksplicitno:

.. code-block:: cpp

  struct A {
      A(int a, int b) {}
  };

  struct B : public A {
      B() : A(2, 3) {}  // klic starševega konstruktorja
  };

Čiste virtualne funkcije in abstraktni razredi
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO


Primer:

.. code-block:: cpp

  #include <string>
  #include <iostream>
  #include <vector>
  #include <memory>

  using namespace std;

  struct Being {
      virtual string zadnje_besede() const = 0;
      void die() {
          cout << zadnje_besede() << endl;
      }
      virtual ostream& print(ostream& os) const {
          return os << "bitje";
      }
      virtual ~Being() {}
  };
  ostream& operator<<(ostream& os, const Being& b) {
      return b.print(os);
  }

  struct Plant : public Being {
      string zadnje_besede() const override {
              return "Screw vegans.";
      }
  };

  struct Animal : public Being {
      virtual string oglasanje() const = 0;
      string zadnje_besede() const override {
          return "Ouch.";
      }
      ostream& print(ostream& os) const override {
          Being::print(os);
          return os << " animal:";
      }
  };

  struct Dog : public Animal {
      string name;
      Dog(string name) : name(name) {}
      string oglasanje() const override {
          return "Hov " + name;
      }
      string zadnje_besede() const override {
          return "Wasn't I a good boy?";
      }
      ostream& print(ostream& os) const override {
          Animal::print(os);
          return os << " Dog: " << name;
      }
  };

  struct Cat : public Animal {
      string oglasanje() const override {
          return "Nyaa";
      }
  };

  struct Duck : public Animal {
      string oglasanje() const override {
          return "Quack";
      }
  };

  int main() {
      // Animal a;

      vector<unique_ptr<Animal>> v;
      v.push_back(make_unique<Dog>("Piki"));
      v.push_back(make_unique<Cat>());
      v.push_back(make_unique<Dog>("Fido"));
      v.push_back(make_unique<Duck>());
      v.push_back(make_unique<Dog>("Jakob"));
      v.push_back(make_unique<Cat>());

      /*
      for (const auto& p : v) {
          cout << p->oglasanje() << endl;
      }*/

      vector<unique_ptr<Being>> b;
      b.push_back(make_unique<Dog>("Piki"));
      b.push_back(make_unique<Cat>());
      b.push_back(make_unique<Duck>());
      b.push_back(make_unique<Plant>());
      for (const auto& p : b) {
          p->die();
          try {
              // cout << typeid(p.get()).name() << endl;
              Animal* a = dynamic_cast<Animal*>(p.get());
              if (a == nullptr) {
                  cout << "a is null" << endl;
              } else {
                  // cout << "here" << endl;
                  cout << a->oglasanje() << endl;
                  // cout << "here" << endl;
              }

          } catch (std::bad_cast& bc) {
              cout << "to ni Animal" << endl;
          }
      }

      cout << "------------------" << endl;
      for (const auto& p : b) {
          cout << *p << endl;
      }


      Dog d("Fifi");
      cout << d << endl;

      return 0;
  }


Daljši primer uporabe - risanje oblik
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

TODO

.. vim: spell spelllang=sl
