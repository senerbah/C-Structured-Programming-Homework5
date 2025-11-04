/************************************************************
 * UBI 503 – Homework 5
 * Simulation: The Tortoise and the Hare (C – Pointers)
 * 
 * Açıklama:
 *  - 70 karelik parkurda Kaplumbağa (T) ve Tavşan (H) yarışı.
 *  - Her “tik”te (saniyede) olasılıklara göre hareket ederler.
 *  - Aynı karede buluşurlarsa "OUCH!!!" basılır.
 *  - Bitiş çizgisi: kare 70. >=70 olan kazanır (beraberlik ele alınır).
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* ---- Sabitler (okunabilirlik için) ----------------------- */
enum {
    TRACK_LEN = 70,     /* Çıktıdaki satır uzunluğu */
    START_POS = 1,      /* Başlangıç karesi */
    FINISH_POS = 70     /* Bitiş çizgisi (kazanma eşiği) */
};

/* ---- İleri bildirimler ----------------------------------- */
static int  rand10(void);
static void clamp_left(int *pos);
static void move_tortoise(int *tPos);
static void move_hare(int *hPos);
static void print_track(int tPos, int hPos, int tick);
static int  race_finished(int tPos, int hPos);
static void print_winner(int tPos, int hPos);

/* ---------------------------------------------------------- */
/* 1..10 arası (dahil) rasgele tamsayı üretir.                 */
static int rand10(void) {
    return 1 + (rand() % 10);
}

/* Konumu 1'in soluna düşmüşse 1'e sabitler. */
static void clamp_left(int *pos) {
    if (*pos < START_POS) {
        *pos = START_POS;
    }
}

/* Kaplumbağa hareketi (olasılıklar probleme uygun). */
static void move_tortoise(int *tPos) {
    int r = rand10();

    if (r >= 1 && r <= 5) {          /* Fast plod: +3 (50%) */
        *tPos += 3;
    } else if (r >= 6 && r <= 7) {   /* Slip: -6 (20%) */
        *tPos -= 6;
    } else {                         /* Slow plod: +1 (30%) */
        *tPos += 1;
    }
    clamp_left(tPos);
}

/* Tavşan hareketi (olasılıklar probleme uygun). */
static void move_hare(int *hPos) {
    int r = rand10();

    if (r >= 1 && r <= 2) {
        /* Sleep: 0 (20%) */
    } else if (r >= 3 && r <= 4) {   /* Big hop: +9 (20%) */
        *hPos += 9;
    } else if (r == 5) {             /* Big slip: -12 (10%) */
        *hPos -= 12;
    } else if (r >= 6 && r <= 8) {   /* Small hop: +1 (30%) */
        *hPos += 1;
    } else {                         /* Small slip: -2 (20%) */
        *hPos -= 2;
    }
    clamp_left(hPos);
}

/* 
 * Tek bir yarış hattını yazar:
 *  - Aynı karede iseler tPos==hPos: tPos-1 boşluk, sonra "OUCH!!!"
 *  - Ayrı karelerde iseler 70 sütunluk bir satırda T ve H gösterilir.
 *  - Çizimde sadece 1..70 arası görünür; mantıksal konumlar ise sınırlandırılmaz.
 */
static void print_track(int tPos, int hPos, int tick) {
    /* Aynı kare: OUCH!!! */
    if (tPos == hPos) {
        int visible = tPos; /* OUCH!!! başlangıç konumu (1-tabanlı) */
        /* 1..(visible-1) arası boşluk */
        for (int i = 1; i < visible && i <= TRACK_LEN; ++i) {
            putchar(' ');
        }
        /* OUCH!!! yaz (satırı taşarsa doğal olarak kırpılır) */
        fputs("OUCH!!!\n", stdout);
        return;
    }

    /* Ayrı karelerde: 70 karakterlik satır */
    for (int i = 1; i <= TRACK_LEN; ++i) {
        int printT = (i == tPos);
        int printH = (i == hPos);

        if (printT && printH) {
            /* Bu duruma normalde girmez (üstte tPos==hPos yakalandı),
               ama koruma amaçlı:
            */
            putchar('X');
        } else if (printT) {
            putchar('T');
        } else if (printH) {
            putchar('H');
        } else {
            putchar(' ');
        }
    }
    putchar('\n');
}

/* Kazanma durumu oluşmuş mu? (en az biri FINISH_POS veya üstünde) */
static int race_finished(int tPos, int hPos) {
    return (tPos >= FINISH_POS) || (hPos >= FINISH_POS);
}

/* Kazanan/beraberlik mesajı basar. */
static void print_winner(int tPos, int hPos) {
    if (tPos >= FINISH_POS && hPos >= FINISH_POS) {
        puts("It's a tie.");
    } else if (tPos >= FINISH_POS) {
        puts("TORTOISE WINS!!! YAY!!!");
    } else {
        puts("Hare wins. Yuch");
    }
}

/* ---------------------------------------------------------- */
int main(int argc, char *argv[]) {
    /* Seed: parametre verilirse onu kullan, yoksa time(NULL) */
    if (argc >= 2) {
        unsigned seed = (unsigned)strtoul(argv[1], NULL, 10);
        srand(seed);
    } else {
        srand((unsigned)time(NULL));
    }

    int tortoisePos = START_POS;
    int harePos     = START_POS;
    int tick        = 0;

    puts("BANG !!!!!");
    puts("AND THEY'RE OFF !!!!!");

    /* Başlangıç çizimi (isteğe bağlı) */
    print_track(tortoisePos, harePos, tick);

    /* Yarış döngüsü */
    while (1) {
        ++tick;

        move_tortoise(&tortoisePos); /* pointer kullanımı istenene uygun */
        move_hare(&harePos);

        print_track(tortoisePos, harePos, tick);

        if (race_finished(tortoisePos, harePos)) {
            print_winner(tortoisePos, harePos);
            break;
        }
    }

    return 0;
}
