STATE PATTERN – LLR

LLR-S1

MSH sınıfı sistem açıldığında varsayılan state olarak NormalState nesnesini başlatmalıdır.
(REQ 2.5)

LLR-S2

MSH, currentState isimli bir HomeState pointer saklamalıdır.
(REQ 2.5)

LLR-S3

HomeState sınıfı aşağıdaki arayüz fonksiyonlarını içermelidir:

enterState(MSH*)

exitState(MSH*)

handle(MSH*)

getName()
(REQ 2.5)

LLR-S4

Tüm state sınıfları (NormalState, HighPerformanceState, LowPowerState, SleepState) HomeState arayüzünden türetilmiş olmalıdır.
(REQ 2.5)

LLR-S5

MSH::changeState() fonksiyonu state değişimi sırasında:

Eski state’in exitState() fonksiyonunu çağırmalı,

State’i güncellemeli,

Yeni state’in enterState() fonksiyonunu çağırmalıdır.
(REQ 2.5)

LLR-S6

Her ConcreteState sınıfı kendi iç davranışını handle() fonksiyonunda tanımlamalıdır.
(REQ 2.5)

LLR-S7

MSH, kullanıcı menüden state değiştirdiğinde changeState() fonksiyonunu çağırarak yeni state’e geçmelidir.
(REQ 2.5)
