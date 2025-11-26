LLR-M1

MSH ilk başlatıldığında varsayılan mode NormalMode olmalıdır.
(REQ 2.4)

LLR-M2

MSH, currentMode adında bir Mode pointer saklamalıdır.
(REQ 2.4)

LLR-M3

Mode arayüzü en az aşağıdaki fonksiyonları içermelidir:

apply(MSH* context)

getName()
(REQ 2.4)

LLR-M4

NormalMode, EveningMode, PartyMode, CinemaMode sınıfları Mode arayüzünden türetilmelidir.
(REQ 2.4)

LLR-M5

Her mode sınıfının apply() fonksiyonu PDF’de verilen davranışları uygulamalıdır:

Normal Mode: light on, TV off, music off

Evening Mode: light off, TV off, music off

Party Mode: light on, TV off, music on

Cinema Mode: light off, TV on, music off
(REQ 2.4)

LLR-M6

MSH changeMode() fonksiyonu ile önceki moda ait çıkışı uygulamaya ihtiyaç duymaz; yeni mod direkt aktif edilmelidir.
(REQ 2.4)

LLR-M7

Kamera, smoke & gas detector cihazları her modda açık kalmalıdır.
(REQ 2.4)

LLR-M8

Mode değişimi kullanıcıya ekranda gösterilmelidir (“Mode changed to …”).
(REQ 2.4)

LLR-M9

Mode değişimi sırasında MSH, ilgili cihazlara konfigürasyonu applyMode() fonksiyonu üzerinden uygulamalıdır.
(REQ 2.4)

LLR-M10

Mode sistemi state sistemiyle bağımsız çalışmalı, birbirini etkilememelidir.
(REQ 2.4)
