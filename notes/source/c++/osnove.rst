Osnove
======

V tem poglavju si bomo ogledali osnove programiranja, s katerimi lahko
vzpostavimo osnovno komunikacijo z računalnikom in naredimo zelo enostavne
programe, pogledali si bomo predpisano strukturo programa in nekaj osnovnih
ukazov.

Osnovna struktura programa
--------------------------
Osnovni "Hello world" program zgleda tako:

.. code-block:: cpp

  #include <iostream>

  int main() {
      std::cout << "Hello world!" << std::endl;
      return 0;
  }

Na začetku so vedno ``#include`` direktive, ki so podobne Pythonovim
``import``-om, ki vključujejo različne knjižnice. V našem primeru vključujemo
knjižnico za input in output (input output stream).

Program izvede vse in samo to, kar se nahaja v funkciji ``main``. Ta funkcija
lahko seveda kliče druge funkcije. Funkcija mora vrniti število, ki pomeni "exit
status" programa in mora biti 0, če je program zaključil uspešno. Vsi naši
programi bodo imeli na koncu ``return 0``.

Vsak stavek se mora končati s podpičjem. Presledki v kodi niso obvezni, tako kot
v Pythonu, zamikanje je samo zaradi berljivosti. Tako je koda kot na primer

.. code-block:: cpp

  int main(){std::cout<<"Hello world!"<<std::endl;return 0;}

sicer veljavna, a
se je izogibajte vsaj toliko kot določenih profesorjev.

C vs. C++ vs. C++11
-------------------
C++ je nadgradnja C-ja, zaradi tega podpira veliko večino C stvari, hkrati pa
nudi svojo novo funkcionalnost. C++ je imel tudi večjo posodobitev leta 2011,
ki je prinesla veliko novosti, ki jih bomo mi z veseljem uporabljali in jih
tudi večina compilerjev že podpira. V splošnem bomo uporabljali bolj C++
funkcije namesto starih C funkcij. Če si boste doma instalirali kakšen
predpotopni compiler, lahko da kakšnih novosti ne bo podpiral, a to ne bi smel
biti hud problem.

Vse funkcije, ki jih podpira standarda knjižnica C++ so v *namespace*-u
``std``. Tako je treba, kot zgoraj v primeru, pred vsako uporabo stvari iz
standardne knjižnice pisati ``std::``. Temu se lahko izognemo, tako da na
začetku programa (za ``#include``-i in pred uporabo funkcij) napišemo ``using
namespace std;``. To sicer ni najbolj higienično v velikih programih saj lahko
povzroči poplavo imen in se temu raje izogibajte, v kratkih programih pa nam
lahko prihrani nekaj pisanja.

Obstajajo C-jevske funkcije za stdio, random, sezname, vendar bomo uporabljali
C++-ovske, pogosto celo C++11.

Spremenljivke
-------------

Spremenljivke so prostori v spominu, ki hranijo določeno vrednost in jih lahko
tekom programa spreminjamo. Vsako spremenljivko moramo deklarirati z njenim
tipom, nato pa ji lahko pripišemo vrednost.

.. code-block:: cpp

  int a;
  a = 8;
  a = 7;
  int b = 9;
  int b;      // compiler error - dvakrat definirana spremenljivka
  c = 6;      //  compiler error - nedefinirana spremenljivka

Če spremenljivki vrednosti ne pripišemo, bo njena vrednost pogosto neko sranje,
ki je ravno takrat v RAM-u, tako da je vse spremenljivke zelo priporočljivo
inicializirati.

Osnovni tipi so ``int`` za števila, ``double`` za decimalna števila, ``bool``
za logične vrednosti in ``char`` za znake.

Komentarji
----------
Komentarji so enovrstični z ``//`` in več vrstični s parom ``/*  */``.

Input in output
---------------
Za manipulacijo standardnega vhoda in izhoda uporabljamo knjižnico
``iostream``, ki definira objekta ``cin`` in ``cout``, s katerima pišemo in
beremo v stdio. Pri nizih to prebere vse do prvega whitespace-a. Če želimo
prebrati celo vrstico uporabimo funkcijo ``getline``.

.. code-block:: cpp

  #include <iostream>

  using namespace std;

  int main() {
      int a;
      cout << "Vpiši število: ";
      cin >> a;
      cout << "Vpisali ste število " << a << endl;
  }

.. note::

  Obstajajo ljudje, ki bodo trdili, da je potrbno uporabljati C-jevski verziji
  ``scanf`` in ``printf``, saj sta mnogo hitrejši. To ni nujno res, pri uporabi
  ``cin`` in ``cout`` se je samo potrebno izgoniti ``endl``, ki neporebno
  flusha in nastaviti ``cin.sync_with_stdio(false)``, da nove verzije pozabijo na
  C funkcije in delujejo samostojno. Za kakršnekoli resne programe je časovna
  razlika nepomembna, veliko več prednosti prinese ekstenzibilnost in
  type-safety.

If stavki
---------
If stavki v C++-u so strukture, ki izvedejo blok kode, samo če je izpolnjen
določen pogoj. *Blok* kode je definiran kot en stavek ali več stavkov znotraj
``{`` in ``}``. Običajna sintaksa ``if`` stavkov:

.. code-block:: cpp

  if (pogoj) {
      koda ...
  } else if (pogoj) {
      koda ...
  } else {
      koda ...
  }

Pogoji so sestavljeni (ponavadi) iz logičnih (``&&``, ``||``, ``!``) in
primerjalnih operatorjev (``==``, ``<``, ``>=``, ...).

Primer:

.. code-block:: cpp

  // program preveri ali je a sodo število
  if (a % 2 == 0) {
      cout << "sodo" << endl;
  } else {
      cout << "liho" << endl;
  }

.. warning::

  Če je v ``if`` stavku en sam stavek, potem lahko oklepaje izpustimo, saj je
  stavek že sam od sebe blok. Zgornjo kodo lahko napišemo tudi tako:

  .. code-block:: cpp

    if (a % 2 == 0)
        cout << "sodo" << endl;
    else
        cout << "liho" << endl;

  To lahko vodi v buge, ko dodamo še en stavek,

  .. code-block:: cpp

    if (a % 2 == 0)
        cout << "sodo" << endl;
    else
        cout << "liho" << endl;
        cout << "vedno" << endl;

  Stavek ``vedno`` se izvede vedno, čeprav indentacija namiguje dugače, kajti
  ``else`` "zagrabi" le en naslednji stavek.

.. danger::

  V C++ je veljavno imeti v ``if`` stavku operator ``=``, ki **nastavi**
  spremenljivke. Torej, človek se zmoti in namesto ``==`` napiše ``=``, kar
  je lahko katastrofalno. Primer:

  .. code-block:: cpp

    if (password_valid = true) {
        // omogoči dostop do bančnih računov in slečenih slik
    } else {
        cout << "Invalid password" << endl;
    }

  Zgornja koda je enaka, ko če bi kar direktno omogočili ves dostop,
  ``password_valid`` se namreč **nastavi** na ``true``, kar tudi vrne
  vrednost ``true`` in je pogoj v ``if`` stavku vedno pravilen.

Obstaja tudi stavek ``switch``, ki se ga ponavadi uporablja kot lepši ``if``,
``else if``. Primer uporabe:

.. code-block:: cpp

  switch (vrednost) {
      case 1:
          // koda
          break;
      case 2:
          // koda
          break;
      case 13:
          // koda
          break;
      default:
          // koda
          break;
  }

Vrednosti pri ``case``-ih morajo biti konstantne in stavek glede na vrednost
spremenljivke ``vrednost`` izvede primerno kodo, če dane vrednosti ni naštete,
potem izvede kodo pod ``default``.

Break pri vsakem case-u je nujen, sicer se izvede tudi koda naslednjega primera
-- tako imenovan "fall through" feature switch stavka.

Primer:

.. code-block:: cpp

  switch (vrednost) {
      case 1:
          // koda 1
      case 2:
          // koda 2
          break;
      case 14:
      case 13:
          // koda
          break;
      default:
          // koda
          break;
  }

Če je vrednost spremenljivke enaka 1, se izvedeta koda 1 in koda 2, ce je
vrednost enaka 2, samo koda 2. Koda za 14 in 13 je enaka.

Zanke
-----

For zanka
~~~~~~~~~

For zanke se uporabljajo za ponavljanje določenega, ponavadi oštevilčenega
opravila do nekega števila ponovitev. Sintaksa:

.. code-block:: cpp

  for (inicializacija; pogoj; korak) {
      // koda
  }

Primer:

.. code-block:: cpp

  for (int i = 0; i < 100; ++i) {
      cout << i << endl;
  }

V C++ obstaja tudi "range for" zanka, ki je podobna Pythonovi ``for`` zanki,
ali pa ``foreach`` zankam v drugih jezikih, ampak si jo bomo pogledali v
poglavju :ref:`range-for`.

While zanka
~~~~~~~~~~~

While zanka se izvaja, dokler je pogoj izpolnjen. Kot pri ``for`` zanki se
zanka lahko ne izvede nikoli, če je pogoj že na začetku neresničen. Sintaksa:

.. code-block:: cpp

  while (pogoj) {
      // koda
  }

Obstaja tudi ``do-while`` zanka, ki je pravzaprav obrnjena ``while`` zanka,
pogoj se preverja na koncu. To pomeni, da se vsa koda v telesu zanke izvede
vsaj enkrat. Sintaksa:

.. code-block:: cpp

  do {
      // koda
  } while (pogoj);

Primer programa, ki od uporabnika bere število :math:`s` in izpiše vse popolne kvadrate manjše od :math:`s`, lihe na
desno, sode na levo. Števila bere dokler so različna od 0.

.. code-block:: cpp

  #include <iostream>
  using namespace std;

  int main() {
      int s;
      cin >> s;

      while (s != 0) {
          for (int i = 1; i*i < s; ++i) {
              if (i % 2 == 1) {
                  cout << "      " << i*i << endl;
              } else {
                  cout << i*i << endl;
              }
          }
          cout << endl;
          cin >> s;
      }
      return 0;
  }

.. danger::

  V pogojih velja enako opozorilo kot pri if stavku -- pazite na operator = v
  pogoju, da ne bi po nesreči spremenili vrednosti spremenljivke.

.. vim: spell spelllang=sl
