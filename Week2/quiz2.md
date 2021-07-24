## 測驗1:

在前述逐字元比對的代碼當中，一個字元要與 0x80 的遮罩做and邏輯:

```c
bool is_ascii_char(const char str[], size_t size)
{
    if (size == 0)
        return false;
    for (int i = 0; i < size; i++)
        if (str[i] & 0x80) /* i.e. (unsigned) str[i] >= 128 */
            return false;
    return true;
}
```

若一次比較 8 個字元，得將每個字元比照先前相同的遮罩，也就是每個字元要與 0x80 比較，那得到的結果就是 8 個位元得與 0x8080808080808080 比較，所以 MMM　代碼為 0x80808080

:::info
延伸問題 1:
解釋上述程式的運作原理，特別是為何用到 memcpy 呢？提示: 與 data alignment 有關，詳閱 C 語言：記憶體管理、對齊及硬體特性
:::

memcpy 在 dest 與 src 有 overlap 的情況下是 UDB (C99 7.21.2.1)，而實際的[GNU Library C 實作](https://github.com/lattera/glibc/blob/master/string/memcpy.c)，我跟著 [RinHizakura 的實驗](https://hackmd.io/@RinHizakura/SJ5NuIANP#Why-memcpy%EF%BC%9F)，閱讀了一遍 GNU C Library 的程式碼，並且重現了一遍 RinHizakura 的實驗，我比較使用 memcpy 版的 is_ascii_array_memcpy 跟使用直接轉型的 is_ascii_array_cast，轉型的版本除了會被 AddressSanitizer 抓出有 misaligned address 以外，用 gdb 觀察記憶體位置，確實 is_ascii_array_memcpy 當中 payload 的記憶體位置為 0 結尾，代表著是 16 bit aligned (於 x86-64 Ubuntu 上測試)，而 is_ascii_array_cat 不是。

```c
bool is_ascii_array_memcpy(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}

bool is_ascii_array_memcpy(const char str[], size_t size)
{
    if (size == 0)
        return false;
    int i = 0;
    while ((i + 8) <= size) {
        uint64_t payload;
        memcpy(&payload, str + i, 8);
        if (payload & 0x8080808080808080)
            return false;
        i += 8;
    }
    while (i < size) {
        if (str[i] & 0x80)
            return false;
        i++;
    }
    return true;
}
```

:::info
延伸問題 2:
將上述技巧應用於「給予一個已知長度的字串，檢測裡頭是否包含有效的英文大小寫字母」
承 (2)，考慮常見的英文標點符號，判斷輸入字串是否為有效的字元集，避免逐一字元比對

提示: Intel SSE 4.2 加入 STTNI (String and Text New Instructions) 指令，可加速字串比對，詳見:
[Schema Validation with Intel® Streaming SIMD Extensions 4](https://software.intel.com/content/www/us/en/develop/articles/schema-validation-with-intel-streaming-simd-extensions-4-intel-sse4.html)
:::

一個簡單的批次取得字串中英文大小寫的程式碼，其實幾乎已經寫在測驗 5 當中，以下為我實作的版本:

```c
```

:::TODO
依照老師的提示研究 Intel SSE 4.2 加入 STTNI (String and Text New Instructions) 指令。
:::


## 測驗2:

可以觀察到回傳的 `return (in + shift) & 0xf` 是 in + shift 的後四位，而 \`0\` - \`9\` 的後四位已經是所求了，所以推測 \`0\` - \`9\` &MASK 的結果會是 0x0，使接下來的 shift 也是 0x0。而 &MASK 加上後面的 bit 位移操作，對 \`a\` - \`f\` 則需要取得 0x9，才能在後面的 return 得到正確結果，猜測 MASK 會對所有 \`a\` - \`f\` 取出同一個 bit 位置為 1 的數值。觀察 \`a\` - \`f\` 的數值值，滿足前兩項條件的 MASK 只有 0x40 或 0xc0，對 \`a\` - \`f\` 取出來的數值為 0x40，因為 shift 要為 0x9 所以可知 AAA 與 BBB 因為 3 和 6。

:::TODO
將 hexchar2val 擴充為允許 "0xFF", "0xCAFEBABE", "0x8BADF00D" 等字串輸入，且輸出對應的十進位數值
:::


## 測驗3 & 測驗4:
已另外有練習

## 測驗5:
`*chunk & PACKED_BYTE(VV1)` 目標是要批次判斷 *chunk 是不是全部都是 acscii 字元，也就是每個 byte 要做某種特定的判斷邏輯，而 PACKED_BYTE(b) 的作用顯然是取出 b 的後 8 個 bits (令其為 0xXY)，轉換成 0xXYXYXYXYXYXYXYXY 的形式，來對 chunk 使用 0xXY 進行逐 byte 的判斷邏輯。參考 測驗1 我們可以知道 VV1 就是 0x80。

先假設 VV2 跟 VV3 為 0，解釋 `*chunk + PACKED_BYTE(128 - 'A' + VV2)` 和 `*chunk + PACKED_BYTE(128 - 'Z' + VV3)`，
我們可以發現，如果 *chunk 的某個 byte >= \`A\` 則前者會大於 128 而溢位，所以同理後者如果此 byte >= 'Z' 則後者會溢位，可以合理猜測我們應該調整後者的判斷邏輯，讓 *chunk > \`Z\` 的時候才溢位，以利後續判斷，所以 VV2 是 0，VV3 是 -1。

:::info
將前述測試程式 main 函式的 char str[] 更換為 char *str，會發生什麼事？請參閱 C 語言規格書，說明 string literal 的行為
:::
參考[RinHizakura 的內容](https://hackmd.io/@RinHizakura/SJ5NuIANP#char-str-or-char-str%EF%BC%9F)

## 測驗6：
:::TODO
:::