package miltin.threads.produtorConsumidor;

public class Teste {

	public static void main(String[] args) {
		Numero n = new Numero(0);
		Produtor p = new Produtor(n);
		Consumidor c = new Consumidor(n);
		Consumidor c1 = new Consumidor(n);
		Consumidor c2 = new Consumidor(n);
		
				
		p.start();
		c.start();
		c1.start();
		c2.start();

	}

}
