# Dokuwiki Kocaeli Üniversitesi Projesi

Bu proje, dosya okuma, yazma ve güncelleme becerilerini geliştirmek için oluşturulmuş bir uygulamadır. Projede, Kocaeli Üniversitesi'ndeki bölümleri ve ders içeriklerini temsil eden bir veri yapısı kullanılmıştır.

## Özellikler

- **Dosya Yapısı:**
  - Ana klasör: `universite/`
  - Alt klasörler: `bolumler/`, `dersler/`
  - `.txt` dosyaları ve diğer formatlarda dosyalar içerir.
  
- **Etiket Yönetimi:**
  - Etiket formatı: `[[kelime]]`, `[[kelime1 kelime2]]`.
  - Hatalı format örnekleri: `[[kelime]`, `[kelime]]`, `[kelime]`, `{{kelime}}`.
  - **Yetim Etiket:** Dosyası bulunmayan etiketler.
  - **İstenen Etiket:** Dosyası var ancak etiket barındırmayan dosyalar.

- **Menü Seçenekleri:**
  - **Arama:** Etiket veya kelime araması yapabilirsiniz.
  - **Güncelleme:**
    - Etiket adlarını değiştirebilirsiniz.
    - Yetim etiketler için dosya oluşturabilirsiniz.
  - **Çıktı Alma:** Tüm etiketlerin ve yetim etiketlerin listesini `output.txt` dosyasına yazabilirsiniz.

## Kurulum

1. **Proje Dosyalarını Klonlayın:**

   ```bash
   git clone https://github.com/kullanici/dokuwiki-projesi.git
   ```

2. **Gerekli Dosyaları Ekleyin:**
   - `universite` klasörü altındaki dosya yapısını düzenleyin:
     - `bolumler/` ve `dersler/` klasörlerini oluşturun.
     - `.txt` dosyalarını ekleyin.

3. **Derleme ve Çalıştırma:**

   ```bash
   gcc -o dokuwiki_program 210202071.c
   ./dokuwiki_program
   ```

## Kullanım

- **Menü Seçenekleri:**
  1. Etiket veya kelime araması yapabilirsiniz.
  2. Etiketlerin adını değiştirebilir ve güncelleyebilirsiniz.
  3. Yetim etiketler için dosya oluşturabilirsiniz.
  4. Tüm sonuçları `output.txt` dosyasına kaydedebilirsiniz.

- **Etiket Formatları:**
  - Doğru: `[[etiket1]]`, `[[etiket1 etiket2]]`
  - Yanlış: `[[etiket1]`, `[etiket1]]`

## Çıktı Örneği

```plaintext
Etiket Listesi       - Tekrar Sayısı
-----------------------------------
[[etiket1]]          3
[[etiket2]]          5

Yetim Etiketler:
[[yetim1]]
[[yetim2]]
```

## Proje Yapısı

```
dokuwiki-projesi/
├── universite/
│   ├── bolumler/
│   └── dersler/
├── 210202071.c
├── output.txt
└── README.md
```

## Katkıda Bulunanlar

Bu proje, Kocaeli Üniversitesi'nin **BLM209 Programlama Laboratuvarı I** dersi kapsamında hazırlanmıştır.


