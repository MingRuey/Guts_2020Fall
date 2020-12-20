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
```

:::info
延伸問題 1:
解釋上述程式的運作原理，特別是為何用到 memcpy 呢？提示: 與 data alignment 有關，詳閱 C 語言：記憶體管理、對齊及硬體特性
:::

參考 [RinHizakura 的實驗](https://hackmd.io/@RinHizakura/SJ5NuIANP#Why-memcpy%EF%BC%9F)，
我比較使用 memcpy 版的 is_ascii_array_memcpy 跟使用 的 is_ascii_array_cast，
觀察記憶體位置的所在位置是否有 unaligned memory access 的問題:

:::info
延伸問題 2:
將上述技巧應用於「給予一個已知長度的字串，檢測裡頭是否包含有效的英文大小寫字母」
承 (2)，考慮常見的英文標點符號，判斷輸入字串是否為有效的字元集，避免逐一字元比對
提示: Intel SSE 4.2 加入 STTNI (String and Text New Instructions) 指令，可加速字串比對，詳見: Schema Validation with Intel® Streaming SIMD Extensions 4
:::

## 測驗2:
