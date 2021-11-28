Uvod
====

C++ je zelo uporabljen in močen jezik, v katerem, ali v njegovem predhodniku
C-ju, so sprogramirani najbolj zahtevni, hitri in znani programi, med drugim vsi
glavni operacijski sistemi, veliko igric, Microsoft Office in sploh večina
stvari, ki vam jih pade na pamet, pa niso na telefonu (razen seveda Android
operacijskega sistema, ki je zopet v C-ju).

C++ je, z razliko od Pythona *prevajan* jezik, kar pomeni, da je kodo najprej
potrebno prevesti v strojno kodo, ki jo potem računalnik izvede. Zaradi tega
vmesnega koraka je tudi za kakšen red velikosti hitrejši od npr. Pythona.

Druga razlika je, da je *statično tipiziran*, kar pomeni, da moramo vsaki
spremenljivki v naprej določiti tip, ki ga potem ne moremo več spreminjati,
kar compilerju omogoča analizo programa in boljše poročanje napak. Primer:
v Pythonu nekje v nekem gnezdenem if stavku seštevate int in string. Vaš
program bo lahko mirno tekel ampak se potem nekoč, ko pride v tisti if sesul.
C++ program se niti prevedel ne bo, sam vam bo compiler povedal da tam
seštevate dva nekompatibilna tipa. Python tega ne more narediti, saj dokler se
program ne izvede do tam, ne ve, kakšnega tipa sta ti dve spremenljivki.

Na začetku se zdijo to mogoče hude omejitve in je potrebno nekaj truda, da se
človek navadi na "malo manj svobode" in "neke čudne napake", vendar te omejitve
lahko vodijo v kodo z manj napakami in kodo z boljšim dizajnom. Program, ko je
enkrat preveden v strojno kodo, je samostojna aplikacija, ki so lahko zaženemo
tudi na drugih računalnikih (z določenimi omejitvami, na primer OS), ne da bi
imeli tam programsko kodo.

C++ je ravno zaradi teh lastnosti zelo uporabljen in zelo močan jezik, ki se ga
zagotovo splača znati. Je sicer eden izmed težjih, toda iz njega sledi veliko
boljše razumevanje delovanja računalnika in programiranja, pa udi druge jezike
se je potem lažje učiti.

Od programske do strojne kode
-----------------------------
Primer programske kode:

.. code-block:: cpp

  #include <iostream>

  int main() {
      std::cout << "Hello world" << std::endl;
      return 0;
  }

Prevajanje v strojno kodo poteka v več korakih
(verjetno obstajajo sloveski izrazi, a se ne bom niti trudil, pa tudi napake ki
jih boste dobivali bodo v angleščini):

Preprocessor
  V naši kodi prebere ``#`` direktive in jih izvede, to vključuje vsebovanje
  header file-ov, makrote, header guarde... (več o tem kasneje)

Compiler
  Kodo, ki jo je izpljunil preprocessor prevede v assembler (zbirni jezik), ki
  je zadnji nivo pred strojno kodo. Na tem koraku program izpiše morebitne
  napake v sintaksi vaše kode, neujemanje tipov, itd... Tem napakam se reče
  "compiler errors" in so daleč najbolj pogoste.

Assembler
  Kodo, ki jo je naredil kompiler spremeni v object datoteke (``.o``), ki so
  že zeli blizu strojni kodi. Tu naj ne bi bilo napak, saj je sicer nekaj
  verjetno narobe s compilerjem, ne pa z vašim programom.

Linker
  Poveže object datoteke v eno zaključeno celoto, tako da računalniku pove, v
  katerih knjižnicah so kakšne funkcije ipd. Tu lahko dobite "linker error", ti
  so ponavadi rezultat tega, da se pozabili prilinkati zraven kakšno zunanjo
  knjižnico ali pa ste napisali in klicali funkcijo brez telesa.

Na koncu je rezultat nekaj, kar razume računalnik, mi pa ne, in se lahko
razlikuje od računalnika do računalnika::

  @@@@@@�@@@@

   ▒ ▒ `▒ `�� 8 8 `8 @@DDP�td@@<<Q�td/lib64/ld-linux-x86-64.so.2GNU
   GNU����8#,�ٴ��fWS�!�

  (E�L� C  �E83 �O �i�@��
  `libstdc++.so.6__gmon_start___Jv_RegisterClasses_ITM_deregisterTMCloneTabl
  e_ITM_registerTMCloneTable_ZNSt8ios_base4InitD1Ev_ZSt4cout_ZStlsISt11char_
  traitsIcEERSt13basic_ostreamIcT_ES5_PKc_ZSt4endlIcSt11char_traitsIcEERSt13
  basic_ostreamIT_T0_ES6__ZNSt8ios_base4InitC1Evlibm.so.6libgcc_s.so.1libc.so
  .6__cxa_atexit__libc_start_mainGLIBC_2.2.5GLIBCXX_3.4.  u▒i      Wt)c8 `� ` X
  `` `h `p `x ` � `� `    H�H�� H��t�#H���5� �%� @�%� h������%� h������%�
  h������%� h������%� h������%� h������%� h�����H��@�� `�b�����
  `�����H�������1�H��fffff.�H��� `��@H��j���1�I��^H��H���PTI�@H��@H���@�1������
  `UH-� `H��H��vH��t]�� `��f�]�fffff.��� `UH��� `H��H��H��H��?H�H��t�H��t ]��
  `��]�fD�=� uUH���n���]�� ��@�0 `H�?u���H��t�UH����]�z���f.�AWAVA��AUATL�%�
  UH�-�
  SI��I��1�L)�H�H�������H��t�L��L��D��A��H��H9�u�H�[]A\A]A^A_�ff.���H�H��Hello
  world<����� ����P����v���Xp��������(zRx ���*zRx $����F▒J
  �?▒;*3$"Dh���"D\����&DDt����eB�B▒�E �B(�H0�H8�O@p8A0A(B B▒B����@ @�@ .  @▒ H@
  `▒( ���o`@�@�@ o ▒@ `��@p0       ▒���o0@���o���o▒@8 `�@�@�@�@�@�@�@GCC: (GNU)
  4.9.0 20140507 (prerelease)GCC: (GNU)
  4.9.1.symtab.strtab.shstrtab.interp.note.ABI-tag.note.gnu.build-id.gnu.hash.
  dynsym.dynstr.gnu.version.gnu.version_r.rela.dyn.rela.plt.init.text.fini.rodata.
  eh_frame_hdr.eh_frame.init_array.fini_array.jcr.dynamic.got.got.plt.data.bss.com
  ment#@ 1<@<$D���o`@`N �@�▒V�@�o^���o▒@▒▒k���o0@0zp@p▒��@��
  ▒�H@H▒�p@p���@���@��@�@<� @      �▒ `▒ �( `( �0 `0 �8 `8 �8 `8 �@ `@ �� `� �
  `� ▒@�0� 8� `�▒ PU@@<@`@�@�@▒0@ p@ �@ H@ �@@@@@  @▒ `( `0 `8 `8 `@ `▒� `�
  `▒�����0 `m(� @�▒ ����� @�0 `��@ `▒( `)▒ `<8 `E ▒� F@g v �@�����@ /t@� �▒�
  `�▒� `�� `�▒� @e�� `� `�C▒��� �@"O `J
  H@init.ccrtstuff.c__JCR_LIST__deregister_tm_clonesregister_tm_clones__do_global
  _dtors_auxcompleted.6617__do_global_dtors_aux_fini_array_entryframe_dummy__
  frame_dummy_init_array_entrya.cpp_GLOBAL__sub_I_main_ZStL8__ioinit__FRAME_END
  ____JCR_END___GLOBAL_OFFSET_TABLE___init_array_end__init_array_start_DYNAMICdata_
  start__libc_csu_fini_start__gmon_start___Jv_RegisterClasses_fini_ZNSt8ios_
  base4InitC1Ev@@GLIBCXX_3.4__libc_start_main@@GLIBC_2.2.5__cxa_atexit@@GLIBC_
  2.2.5_ZNSt8ios_base4InitD1Ev@@GLIBCXX_3.4_ITM_deregisterTMCloneTable_
  ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@@GLIBCXX_3.4_IO_stdin_
  used_ITM_registerTMCloneTable__data_start__TMC_END___ZSt4cout@@GLIBCXX_3.4__
  dso_handle__libc_csu_init__bss_start_end_ZSt4endlIcSt11char_traitsIcEERSt13
  basic_ostreamIT_T0_ES6_@@GLIBCXX_3.4_edatamain_init

Nekaj podobnega dobite, če odprete katerikoli ``.exe`` file v beležnici.

Potek dela
----------

C++ kodo napišete v vašem text-editorju in jo shranite v datoteko s končnico
``.cpp`` ali ``.cc``. V primeru bomo uporabljali ``program.cpp``.

Zaženete:
``g++ -o program program.cpp``
in ukaz na vašem sistemu naredi datoteko ``program`` ali ``program.exe``, ki jo
zaženete preprosto s ``./program`` ali ``program.exe``. Zastavica ``-o``
pomeni output filename. Dodamo lahko se veliko zastavic, opisanih spodaj.

``g++`` pogosto javi napake -- to pomeni da program ni pravilno napisan in ga
ne more prevesti -- napake morate odpraviti, sicer ne morate dobiti executable
datoteke in ga niti zagnati ne morete (v Pythonu se zgodi nekaj podobnega ce
date v if enojni =). Tudi ko je program že preveden, se lahko med tekom
programa sesuje (v Pythonu je to precej pogosto) in najpogostejša napaka je
``segmentation fault``, ki pomeni da ste nekaj zamuštrali s spomniom: ali vam
ga je zmanjkalo, ste sli cez seznam, neskončna rekurzija itd... Če delite z 0,
dobite floating point exception, itd...

Dve zelo priporočeni zastavici za ``g++`` sta ``-std=c++11`` in ``-Wall``, ki
omogočita prevajanje jezika, napisanega v novejšem standardu in izpišeta
dodatna opozorila o napakah v kodi.

Program torej ponavadi poženemo z:

.. code-block:: bash

  g++ -std=c++11 -Wall -o program program.cpp

.. note::

  Če želite iz compilerja barvni output, potem je treba dodati še zastavico
  ``-fdiagnostics-color=always``.

.. note::

  Obstajajo tudi drugi prevajalniki, znan je tudi clang++, ki se ga uporablja
  popolnoma enako. Znan pa je potem da je velikrat hitrejši, ima pa tudi veliko
  lepša poročila o napakah. (kar velikrat zelo pomaga).

.. vim: spell spelllang=sl
