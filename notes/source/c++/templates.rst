Predloge (templates)
--------------------

Recimo, da želimo napisati funkcijo ``max``, ki sprejme dve vrednosti in vrne
večjo izmed obeh.

Za števila bi jo napisali recimo tako:

.. code-block:: cpp

  int max(int x, int y) {
      if (x > y) {
          return x;
      } else {
          return y;
      }
  }

Zelo podobna bi bila funkcija za ``double``:

.. code-block:: cpp

  double max(double x, double y) {
      if (x > y) {
          return x;
      } else {
          return y;
      }
  }

Če bi jo želeli napisati za kater drug tip, bi prav tako izgledala zelo
podobno. Da se izognemo temu nepotrebnemu ponavaljanju kode, lahko napišemo eno
samo funkcijo, ki deluje za splošen tip ``T``. Zapišemo jo tako:

.. code-block:: cpp

  template <typename T>
  T max(T x, T y) {
      if (x > y) {
          return x;
      } else {
          return y;
      }
  }

Beseda ``template`` pred funkcijo označuje, da je ta funkcija predloga, zvevza
``typename T``, pa pomeni, da ``T`` označuje naš neznani tip. Namesto besedice
``typename`` lahko uporabimo tudi ``class``. Ko funkcijo
pokličemo z npr. ``max(1.2, 4.5)``, prevajalnik sam ve, da smo jo poklicali z
dvema parametroma tipa ``double`` in v predlogo vstavi namesto ``T`` tip ``double``
ter dobi funkcijo, kot smo jo napisali prej.

Če pa bi npr. želeli funkcijo poklicati kot ``max(3, 1.2)``, torej s
parametroma ``int`` in ``double``, pa se koda ne bi prevedla, saj morata biti v
predlogi oba tipa enaka (oba sta ``T``).

.. code-block:: none

  a.cpp:16:23: error: no matching function for call to ‘max(int, double)’
       cout << max(3, 1.2) << endl;
                         ^
  a.cpp:7:3: note: candidate: template<class T> T max(T, T)
   T max(T x, T y) {
     ^~~
  a.cpp:7:3: note:   template argument deduction/substitution failed:
  a.cpp:16:23: note:   deduced conflicting types for parameter ‘T’ (‘int’ and ‘double’)
       cout << max(3, 1.2) << endl;
                         ^


TODO: Funckije s poljubno argumenti, templated classes.

.. vim: spell spelllang=sl
