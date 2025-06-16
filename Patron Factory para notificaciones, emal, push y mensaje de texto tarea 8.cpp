#include <iostream>
#include <string>
using namespace std;

class INotificacion {
public:
    virtual void enviar(const string& mensaje) = 0;
    virtual ~INotificacion() {}
};
class EmailNotificacion : public INotificacion {
public:
    void enviar(const string& mensaje) override {
        cout << "[EMAIL] Enviando email: " << mensaje << endl;
    }
};
class PushNotificacion : public INotificacion {
public:
    void enviar(const string& mensaje) override {
        cout << "[PUSH] Enviando notificación push: " << mensaje << endl;
    }
};
class SMSNotificacion : public INotificacion {
public:
    void enviar(const string& mensaje) override {
        cout << "[SMS] Enviando mensaje de texto: " << mensaje << endl;
    }
};
class NotificacionFactory {
public:
    virtual INotificacion* crearNotificacion() = 0;
    virtual ~NotificacionFactory() {}
};

class EmailFactory : public NotificacionFactory {
public:
    INotificacion* crearNotificacion() override {
        return new EmailNotificacion();
    }
};

class PushFactory : public NotificacionFactory {
public:
    INotificacion* crearNotificacion() override {
        return new PushNotificacion();
    }
};
class SMSFactory : public NotificacionFactory {
public:
    INotificacion* crearNotificacion() override {
        return new SMSNotificacion();
    }
};

void enviarAlerta(NotificacionFactory* factory, const string& mensaje) {
    INotificacion* noti = factory->crearNotificacion();
    noti->enviar(mensaje);
    delete noti;
}

int main() {
    EmailFactory emailFactory;
    PushFactory pushFactory;
    SMSFactory smsFactory;

    enviarAlerta(&emailFactory, "Tu pedido ha sido confirmado.");
    enviarAlerta(&pushFactory, "Tienes una nueva oferta.");
    enviarAlerta(&smsFactory, "Código de verificación: 123456");

    return 0;
}
