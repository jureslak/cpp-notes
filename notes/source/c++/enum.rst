.. _enumcpp:

Enum
====

Tipi, deklarirani z besedo ``enum`` so posebni tipi, ki
predstavljajo naštevanje (enumeration) neke končne skupne možnosti.
Običajne ``enum``-e se definira preprosto tako, da naštejemo vse možnosti:

.. code-block:: cpp

  enum Color { RED, YELLOW, GREEN };

Sedaj lahko tip ``Color`` uporabljamo kot običajen tip, le da ima lahko le tri
vrednosti:


.. code-block:: cpp

  Color c = RED;
  if (c == GREEN) {
     ...
  }

Zelo pogosto se ``enum``-e uporablja v povezavi s ``switch``
stavkom:

.. code-block:: cpp

  switch (c) {
      case RED:  ...; break;
      case YELLOW:  ...; break;
      case YELLOW: ...; break;
  }

Tu se lahko za vsako izmed končno mnogo možnosti odločimo, kaj bomo naredili,
prevajalnik pa nas posvari, če smo katero pozabili.

S C++11 so prišli tudi t. i. *scoped enumerations*, ki se jih definira podobno,
s kombinacijo ``enum class``:

.. code-block:: cpp

  enum class Color { RED, YELLOW, GREEN };

razlika pa je, da moramo pri uporabi njihovih vrednostih pisati tip, ki mu
vrednosti pripadajo (zato *scoped*)

.. code-block:: cpp

  Color c = Color::RED;

Prav tako lahko določimo kateri tip se v ozadju uporabi za vrednosti. Pri stari
verziji je to vedno ``int`` (in možnosti se začnejo šteti od 0 naprej, če ne
povemo drugače),
pri novejšh, pa lahko izberemo drug tip, kot npr. ``char``:

.. code-block:: cpp

  enum class Color : char { RED, YELLOW, GREEN };

Še ena razlika je, da se novejši enumi se ne morejo avtomatsko pretvoriti v svoj
implementacijski tip, starejši pa se lahko.

.. code-block:: cpp

  int c = RED;  // ok
  char b = Color::RED;  //  error: cannot convert ‘Color’ to ‘char’ in initialization

.. vim: spell spelllang=sl
