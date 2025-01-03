/*

  Класс общего предка всех ядер серии K145, имеющих память M для подключения в магистраль 145 серии

   все методы данного класса могут быть переопределны конкретным наследником

*/
#ifndef K145_OWNER_CLASS
#define K145_OWNER_CLASS

#include "cascade.h"
#include "chargemem.h"

class K145 : public CASCADE
{
  protected:
    K145 *BUSi, *BUSo;                  // входящая магистральная линия и исходящая магистральная линия

  public:
    CHARGE_MEM *M;

    K145();                             // конструктор класса
    ~K145();                            // деструктор убирающий размещение М

    virtual void clk(int phase);        // Тактовый сигнал с указанием фазы - phase
    virtual const char* about(void) const;    // Возвращает информацию чипа "о себе"
    virtual K145* Target(void);         // Метод возвращает устройство закаскадированное на вход магистральной линии
    virtual void out_to(K145 *ms);      // Назначение ведомого устройства на магистрали
    char get(void) const override;      // Метод возвращающий в магистральный канал выход памяти M

};

#endif
