LLR-01: Camera ve SmokeGasDetector sınıfları, durum değişikliğini bildirmek için Observer örüntüsünün ISubject arayüzünü uygulayacaktır.

LLR-02: SecuritySystem ve DetectionSystem sınıfları, sensör bildirimlerini almak için Observer örüntüsünün IObserver arayüzünü uygulayacaktır.

LLR-03: SecuritySystem, yalnızca Kameradan gelen "MOTION_DETECTED" bildirimini aldığında, kendi Güvenlik Zincirini başlatacaktır.

LLR-04: DetectionSystem, yalnızca Dedektörlerden gelen "DANGER_DETECTED" bildirimini aldığında, kendi Algılama Zincirini başlatacaktır.

LLR-05: Güvenlik Zinciri, Chain of Responsibility örüntüsü kullanılarak Alarm → Işık Açma → Polis Arama sırasıyla, kesintisiz bir akışta kurulacaktır.

LLR-06: Algılama Zinciri, Chain of Responsibility örüntüsü kullanılarak Alarm → Işık Flaşlama → İtfaiye Arama sırasıyla, kesintiye uğratılabilir bir akışta kurulacaktır.

LLR-07: Algılama Zincirindeki AlarmAction işleyicisi, 10 saniye içinde kullanıcıdan onay alarak, başarılı olması durumunda zincirin sonraki halkaya aktarılmasını engelleyecektir (Senaryo Adım 25).

LLR-08: CoR halkaları olan CallPoliceAction (Güvenlik zinciri için) ve CallFireStationAction (Algılama zinciri için) sınıfları, ilgili zincirlerin son eylemini gerçekleştiren son halkalar olacaktır.
