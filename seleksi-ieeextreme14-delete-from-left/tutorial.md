Perhatikan hasil akhir ketika A dan B bernilai sama. Karena kita menghapus huruf-huruf A dan B dari kiri, maka
di akhir yang tersisa adalah suffix (akhiran) dari A dan B. Sehingga, common word yang menjadi hasil akhir A
dan B merupakan common suffix dari mereka. Untuk melakukan langkah minimal, maka yang tersisa tentu saja harus
merupakan longest common suffix. Untuk mencari panjang ini dapat dilakukan dengan iterasi dari huruf terakhir, huruf kedua terakhir, dan seterusnya hingga ada huruf yang berbeda atau hurufnya sudah habis. 

Kompleksitas O(min(|A|, |B|)).