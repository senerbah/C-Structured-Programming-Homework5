# 🐢🏁 UBI503 – Data Structures and Algorithms  
## Homework 5 – Simulation: *The Tortoise and the Hare*

**Öğrenci:** Bahtınur Şener  
**Numara:** 91250000022  
**Dönem:** 2025–2026 Güz  
**Kurum:** Ege Üniversitesi – Fen Bilimleri Enstitüsü – Uluslararası Bilgisayar  
**Ders:** Veri Yapıları ve Algoritmalar (UBI 503)  
**Ödev Tarihi:** 04.11.2025  
**Teslim Tarihi:** 11.11.2025  

---

## 📘 Problem Tanımı

Bu ödevde klasik “Kaplumbağa ile Tavşan” yarışının **bilgisayar simülasyonu** gerçekleştirilmiştir.  
Kaplumbağa (T) ve Tavşan (H), **1. kareden** başlayıp **70. kareye** ulaşmaya çalışırlar.  
Her saniyede (clock tick) her iki hayvanın pozisyonu, olasılık tablosuna göre rastgele belirlenir.

Yarışta:
- Aynı kareye denk gelirlerse **OUCH!!!** yazdırılır.  
- 70. kareye ilk ulaşan kazanır.  
- Eğer ikisi aynı anda 70’i geçerse **beraberlik** olur.

---

## 🎯 Beklenti

- **Pointer kullanımı:** Hareket fonksiyonları konum değişkenlerini pointer ile alır.  
- **Fonksiyon yapısı:** Kod yapısal programlama ilkelerine uygun, yorumlarla açıklanmıştır.  
- **Çıktı formatı:** 70 karelik çizgi üzerinde `T`, `H` veya `OUCH!!!` gösterilir.  
- **Kazanma durumu:**  
  - Kaplumbağa kazanırsa → `TORTOISE WINS!!! YAY!!!`  
  - Tavşan kazanırsa → `Hare wins. Yuch`  
  - Beraberlik → `It's a tie.`  

---

## 🔢 Olasılık Tablosu

| **Hayvan** | **Hareket Tipi** | **Olasılık (%)** | **Hareket (kare)** |
|-------------|------------------|------------------|---------------------|
| **Kaplumbağa** | Fast Plod | 50 | +3 |
| | Slip | 20 | −6 |
| | Slow Plod | 30 | +1 |
| **Tavşan** | Sleep | 20 | 0 |
| | Big Hop | 20 | +9 |
| | Big Slip | 10 | −12 |
| | Small Hop | 30 | +1 |
| | Small Slip | 20 | −2 |

---

## ⚙️ Program Akışı

1. Rasgele sayı üretilir (`1–10` arası).  
2. Kaplumbağa ve tavşan fonksiyonları çağrılır.  
3. Konumlar güncellenir; 1’in altına düşerse **1’e sabitlenir.**  
4. Ekranda 70 karakterlik çizgi basılır:
   - `T` → Kaplumbağa  
   - `H` → Tavşan  
   - `OUCH!!!` → Aynı karede karşılaşma  
5. Bir hayvan 70’e ulaşırsa sonuç yazdırılır ve yarış biter.

---

