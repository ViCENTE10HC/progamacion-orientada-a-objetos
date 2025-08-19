// Sistema Bancario Completo en JavaScript
class SistemaBancario {
    constructor() {
        this.usuarios = new Map();
        this.sesionActual = null;
        this.transacciones = [];
        this.notificaciones = [];
        this.inicializar();
    }

    inicializar() {
        console.log("🏦 Sistema Bancario Inicializado");
        console.log("=".repeat(50));
        this.mostrarMenu();
    }

    // SISTEMA DE REGISTRO Y AUTENTICACIÓN
    registrarUsuario(datos) {
        const { nombre, email, telefono, password, documentoId } = datos;
        
        if (this.usuarios.has(email)) {
            throw new Error("El email ya está registrado");
        }

        const numeroAccount = this.generarNumeroCuenta();
        const usuario = {
            id: Date.now().toString(),
            nombre,
            email,
            telefono,
            password,
            documentoId,
            numeroCuenta: numeroAccount,
            saldo: 1000.00, // Saldo inicial de bienvenida
            tarjetas: [],
            historialTransacciones: [],
            fechaRegistro: new Date(),
            activo: true
        };

        // Crear tarjeta de débito automáticamente
        usuario.tarjetas.push(this.crearTarjeta(usuario.id, 'debito'));

        this.usuarios.set(email, usuario);
        this.enviarNotificacion(usuario, 'sms', `¡Bienvenido ${nombre}! Tu cuenta ha sido creada exitosamente. Número: ${numeroAccount}`);
        this.enviarNotificacion(usuario, 'email', `Cuenta bancaria creada. Saldo inicial: $${usuario.saldo}`);
        
        console.log(`✅ Usuario registrado: ${nombre}`);
        console.log(`📱 Número de cuenta: ${numeroAccount}`);
        console.log(`💰 Saldo inicial: $${usuario.saldo}`);
        return usuario;
    }

    iniciarSesion(email, password) {
        const usuario = this.usuarios.get(email);
        if (!usuario) {
            throw new Error("Usuario no encontrado");
        }
        if (usuario.password !== password) {
            throw new Error("Contraseña incorrecta");
        }
        if (!usuario.activo) {
            throw new Error("Cuenta desactivada");
        }

        this.sesionActual = usuario;
        this.enviarNotificacion(usuario, 'sms', `Inicio de sesión detectado en ${new Date().toLocaleString()}`);
        console.log(`🔓 Sesión iniciada para: ${usuario.nombre}`);
        return usuario;
    }

    cerrarSesion() {
        if (this.sesionActual) {
            console.log(`🔒 Sesión cerrada para: ${this.sesionActual.nombre}`);
            this.sesionActual = null;
        }
    }

    // GESTIÓN DE TARJETAS
    crearTarjeta(usuarioId, tipo = 'debito') {
        return {
            id: Date.now().toString() + Math.random().toString(36).substr(2, 9),
            numero: this.generarNumeroTarjeta(),
            tipo: tipo,
            cvv: this.generarCVV(),
            fechaVencimiento: this.calcularFechaVencimiento(),
            limite: tipo === 'credito' ? 5000 : null,
            saldoCredito: tipo === 'credito' ? 5000 : null,
            activa: true,
            fechaCreacion: new Date()
        };
    }

    solicitarTarjetaCredito() {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        
        const tarjetaCredito = this.crearTarjeta(this.sesionActual.id, 'credito');
        this.sesionActual.tarjetas.push(tarjetaCredito);
        
        this.enviarNotificacion(this.sesionActual, 'email', 
            `Nueva tarjeta de crédito aprobada. Número: **** **** **** ${tarjetaCredito.numero.slice(-4)}`);
        
        console.log(`💳 Tarjeta de crédito creada: **** **** **** ${tarjetaCredito.numero.slice(-4)}`);
        return tarjetaCredito;
    }

    // OPERACIONES BANCARIAS
    consultarSaldo() {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        
        console.log(`💰 Saldo actual: $${this.sesionActual.saldo.toFixed(2)}`);
        
        // Mostrar información de tarjetas
        this.sesionActual.tarjetas.forEach(tarjeta => {
            if (tarjeta.tipo === 'credito') {
                console.log(`💳 Crédito disponible: $${tarjeta.saldoCredito.toFixed(2)}`);
            }
        });
        
        return this.sesionActual.saldo;
    }

    realizarDeposito(monto, concepto = 'Depósito') {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        if (monto <= 0) throw new Error("El monto debe ser positivo");

        this.sesionActual.saldo += monto;
        
        const transaccion = {
            id: Date.now().toString(),
            tipo: 'deposito',
            monto: monto,
            concepto: concepto,
            fecha: new Date(),
            saldoAnterior: this.sesionActual.saldo - monto,
            saldoNuevo: this.sesionActual.saldo,
            usuario: this.sesionActual.email
        };

        this.sesionActual.historialTransacciones.push(transaccion);
        this.transacciones.push(transaccion);

        this.enviarNotificacion(this.sesionActual, 'sms', 
            `Depósito realizado: $${monto.toFixed(2)}. Nuevo saldo: $${this.sesionActual.saldo.toFixed(2)}`);
        
        console.log(`💵 Depósito realizado: $${monto.toFixed(2)}`);
        console.log(`💰 Nuevo saldo: $${this.sesionActual.saldo.toFixed(2)}`);
        
        return transaccion;
    }

    realizarRetiro(monto, concepto = 'Retiro') {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        if (monto <= 0) throw new Error("El monto debe ser positivo");
        if (monto > this.sesionActual.saldo) throw new Error("Saldo insuficiente");

        this.sesionActual.saldo -= monto;
        
        const transaccion = {
            id: Date.now().toString(),
            tipo: 'retiro',
            monto: monto,
            concepto: concepto,
            fecha: new Date(),
            saldoAnterior: this.sesionActual.saldo + monto,
            saldoNuevo: this.sesionActual.saldo,
            usuario: this.sesionActual.email
        };

        this.sesionActual.historialTransacciones.push(transaccion);
        this.transacciones.push(transaccion);

        this.enviarNotificacion(this.sesionActual, 'sms', 
            `Retiro realizado: $${monto.toFixed(2)}. Nuevo saldo: $${this.sesionActual.saldo.toFixed(2)}`);
        
        console.log(`💸 Retiro realizado: $${monto.toFixed(2)}`);
        console.log(`💰 Nuevo saldo: $${this.sesionActual.saldo.toFixed(2)}`);
        
        return transaccion;
    }

    realizarTransferencia(emailDestino, monto, concepto = 'Transferencia') {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        if (monto <= 0) throw new Error("El monto debe ser positivo");
        if (monto > this.sesionActual.saldo) throw new Error("Saldo insuficiente");
        
        const usuarioDestino = this.usuarios.get(emailDestino);
        if (!usuarioDestino) throw new Error("Usuario destinatario no encontrado");

        // Debitar del remitente
        this.sesionActual.saldo -= monto;
        
        // Acreditar al destinatario
        usuarioDestino.saldo += monto;

        const transaccionEnvio = {
            id: Date.now().toString(),
            tipo: 'transferencia_enviada',
            monto: monto,
            concepto: concepto,
            fecha: new Date(),
            destinatario: emailDestino,
            saldoAnterior: this.sesionActual.saldo + monto,
            saldoNuevo: this.sesionActual.saldo,
            usuario: this.sesionActual.email
        };

        const transaccionRecepcion = {
            id: (Date.now() + 1).toString(),
            tipo: 'transferencia_recibida',
            monto: monto,
            concepto: concepto,
            fecha: new Date(),
            remitente: this.sesionActual.email,
            saldoAnterior: usuarioDestino.saldo - monto,
            saldoNuevo: usuarioDestino.saldo,
            usuario: emailDestino
        };

        this.sesionActual.historialTransacciones.push(transaccionEnvio);
        usuarioDestino.historialTransacciones.push(transaccionRecepcion);
        this.transacciones.push(transaccionEnvio, transaccionRecepcion);

        // Notificaciones
        this.enviarNotificacion(this.sesionActual, 'sms', 
            `Transferencia enviada: $${monto.toFixed(2)} a ${emailDestino}. Nuevo saldo: $${this.sesionActual.saldo.toFixed(2)}`);
        
        this.enviarNotificacion(usuarioDestino, 'sms', 
            `Transferencia recibida: $${monto.toFixed(2)} de ${this.sesionActual.email}. Nuevo saldo: $${usuarioDestino.saldo.toFixed(2)}`);

        console.log(`💸 Transferencia enviada: $${monto.toFixed(2)} a ${emailDestino}`);
        console.log(`💰 Nuevo saldo: $${this.sesionActual.saldo.toFixed(2)}`);
        
        return { envio: transaccionEnvio, recepcion: transaccionRecepcion };
    }

    // PAGOS CON TARJETA
    pagarConTarjeta(numeroTarjeta, monto, comercio, cvv) {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        
        const tarjeta = this.sesionActual.tarjetas.find(t => t.numero === numeroTarjeta);
        if (!tarjeta) throw new Error("Tarjeta no encontrada");
        if (!tarjeta.activa) throw new Error("Tarjeta desactivada");
        if (tarjeta.cvv !== cvv) throw new Error("CVV incorrecto");

        let fondosDisponibles;
        
        if (tarjeta.tipo === 'debito') {
            fondosDisponibles = this.sesionActual.saldo;
            if (monto > fondosDisponibles) throw new Error("Saldo insuficiente");
            this.sesionActual.saldo -= monto;
        } else {
            fondosDisponibles = tarjeta.saldoCredito;
            if (monto > fondosDisponibles) throw new Error("Límite de crédito excedido");
            tarjeta.saldoCredito -= monto;
        }

        const transaccion = {
            id: Date.now().toString(),
            tipo: `pago_${tarjeta.tipo}`,
            monto: monto,
            concepto: `Pago en ${comercio}`,
            fecha: new Date(),
            tarjeta: `**** **** **** ${numeroTarjeta.slice(-4)}`,
            comercio: comercio,
            saldoAnterior: tarjeta.tipo === 'debito' ? this.sesionActual.saldo + monto : tarjeta.saldoCredito + monto,
            saldoNuevo: tarjeta.tipo === 'debito' ? this.sesionActual.saldo : tarjeta.saldoCredito,
            usuario: this.sesionActual.email
        };

        this.sesionActual.historialTransacciones.push(transaccion);
        this.transacciones.push(transaccion);

        this.enviarNotificacion(this.sesionActual, 'sms', 
            `Pago realizado: $${monto.toFixed(2)} en ${comercio} con tarjeta **** ${numeroTarjeta.slice(-4)}`);

        console.log(`💳 Pago realizado: $${monto.toFixed(2)} en ${comercio}`);
        console.log(`💰 ${tarjeta.tipo === 'debito' ? 'Nuevo saldo' : 'Crédito disponible'}: $${(tarjeta.tipo === 'debito' ? this.sesionActual.saldo : tarjeta.saldoCredito).toFixed(2)}`);
        
        return transaccion;
    }

    // SISTEMA DE NOTIFICACIONES
    enviarNotificacion(usuario, tipo, mensaje) {
        const notificacion = {
            id: Date.now().toString() + Math.random().toString(36).substr(2, 9),
            usuario: usuario.email,
            tipo: tipo, // 'sms', 'email', 'push'
            mensaje: mensaje,
            fecha: new Date(),
            leida: false
        };

        this.notificaciones.push(notificacion);
        
        // Simular envío
        if (tipo === 'sms') {
            console.log(`📱 SMS a ${usuario.telefono}: ${mensaje}`);
        } else if (tipo === 'email') {
            console.log(`📧 Email a ${usuario.email}: ${mensaje}`);
        }
        
        return notificacion;
    }

    verNotificaciones() {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        
        const notificacionesUsuario = this.notificaciones
            .filter(n => n.usuario === this.sesionActual.email)
            .sort((a, b) => b.fecha - a.fecha);

        console.log("\n📬 NOTIFICACIONES:");
        console.log("=".repeat(30));
        
        if (notificacionesUsuario.length === 0) {
            console.log("No hay notificaciones");
        } else {
            notificacionesUsuario.forEach((notif, index) => {
                const estado = notif.leida ? "✅" : "🔔";
                console.log(`${estado} [${notif.tipo.toUpperCase()}] ${notif.mensaje}`);
                console.log(`   📅 ${notif.fecha.toLocaleString()}`);
                console.log("");
            });
        }

        return notificacionesUsuario;
    }

    // HISTORIAL DE TRANSACCIONES
    verHistorial(limite = 10) {
        if (!this.sesionActual) throw new Error("Debe iniciar sesión");
        
        const historial = this.sesionActual.historialTransacciones
            .sort((a, b) => b.fecha - a.fecha)
            .slice(0, limite);

        console.log("\n📊 HISTORIAL DE TRANSACCIONES:");
        console.log("=".repeat(40));
        
        if (historial.length === 0) {
            console.log("No hay transacciones");
        } else {
            historial.forEach(t => {
                const simbolo = this.obtenerSimboloTransaccion(t.tipo);
                console.log(`${simbolo} ${t.concepto} - $${t.monto.toFixed(2)}`);
                console.log(`   📅 ${t.fecha.toLocaleString()}`);
                console.log(`   💰 Saldo: $${t.saldoNuevo.toFixed(2)}`);
                console.log("");
            });
        }

        return historial;
    }

    // UTILIDADES Y GENERADORES
    generarNumeroCuenta() {
        return '4000' + Math.floor(Math.random() * 100000000).toString().padStart(8, '0');
    }

    generarNumeroTarjeta() {
        return '4' + Math.floor(Math.random() * 1000000000000000).toString().padStart(15, '0');
    }

    generarCVV() {
        return Math.floor(Math.random() * 900 + 100).toString();
    }

    calcularFechaVencimiento() {
        const fecha = new Date();
        fecha.setFullYear(fecha.getFullYear() + 4);
        return fecha;
    }

    obtenerSimboloTransaccion(tipo) {
        const simbolos = {
            'deposito': '💵',
            'retiro': '💸',
            'transferencia_enviada': '📤',
            'transferencia_recibida': '📥',
            'pago_debito': '💳',
            'pago_credito': '💳'
        };
        return simbolos[tipo] || '💼';
    }

    // INTERFAZ DE USUARIO (CONSOLA)
    mostrarMenu() {
        console.log("\n🏦 MENU PRINCIPAL:");
        console.log("1. Registrar usuario");
        console.log("2. Iniciar sesión");
        console.log("3. Cerrar sesión");
        console.log("4. Consultar saldo");
        console.log("5. Realizar depósito");
        console.log("6. Realizar retiro");
        console.log("7. Transferir dinero");
        console.log("8. Pagar con tarjeta");
        console.log("9. Solicitar tarjeta de crédito");
        console.log("10. Ver historial");
        console.log("11. Ver notificaciones");
        console.log("12. Salir");
        console.log("");
    }

    // MÉTODOS PARA TESTING
    ejecutarDemo() {
        console.log("🔄 EJECUTANDO DEMO DEL SISTEMA BANCARIO");
        console.log("=".repeat(50));
        
        try {
            // Registrar usuarios de prueba
            const usuario1 = this.registrarUsuario({
                nombre: "Juan Pérez",
                email: "juan@email.com",
                telefono: "+52-555-1234",
                password: "123456",
                documentoId: "CURP123456"
            });

            const usuario2 = this.registrarUsuario({
                nombre: "María García",
                email: "maria@email.com",
                telefono: "+52-555-5678",
                password: "654321",
                documentoId: "CURP654321"
            });

            // Iniciar sesión con usuario1
            this.iniciarSesion("juan@email.com", "123456");
            
            // Realizar operaciones
            this.consultarSaldo();
            this.realizarDeposito(500, "Depósito inicial adicional");
            this.solicitarTarjetaCredito();
            
            const tarjetaDebito = this.sesionActual.tarjetas.find(t => t.tipo === 'debito');
            this.pagarConTarjeta(tarjetaDebito.numero, 100, "Supermercado XYZ", tarjetaDebito.cvv);
            
            this.realizarTransferencia("maria@email.com", 200, "Pago prestamo");
            
            this.verHistorial(5);
            this.verNotificaciones();
            
            console.log("\n✅ DEMO COMPLETADO EXITOSAMENTE");
            
        } catch (error) {
            console.error("❌ Error en demo:", error.message);
        }
    }
}

// INICIALIZAR Y EJECUTAR EL SISTEMA
const banco = new SistemaBancario();

// Para usar el sistema, puedes llamar a los métodos directamente:
console.log("\n🚀 Para usar el sistema, utiliza los siguientes comandos:");
console.log("banco.ejecutarDemo() - Ejecutar demostración completa");
console.log("banco.registrarUsuario({...}) - Registrar nuevo usuario");
console.log("banco.iniciarSesion(email, password) - Iniciar sesión");
console.log("banco.consultarSaldo() - Ver saldo actual");
console.log("banco.realizarDeposito(monto) - Hacer depósito");
console.log("banco.realizarTransferencia(email, monto) - Transferir dinero");
console.log("\n💡 Ejecuta 'banco.ejecutarDemo()' para ver el sistema en acción!");

// Exportar para uso externo si es necesario
if (typeof module !== 'undefined' && module.exports) {
    module.exports = { SistemaBancario, banco };
}
