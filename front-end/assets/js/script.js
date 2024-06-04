// http://localhost:8080/api/v1/dendro
URL = 'https://sv95h56n-8081.brs.devtunnels.ms/api/v1/dendro';

// Função para obter os parâmetros da URL
const urlSearchParams = new URLSearchParams(window.location.search);
const dendroId = urlSearchParams.get('id');

const dendroPage = document.querySelector('.dendro-page');

// Função para ler as estufas
const readDendros = async () => {

  let dendros = document.querySelector('.dendros');
  dendros.innerHTML = '<div class="loading">Carregando...</div>';

  let response = await fetch(URL);
  let json = await response.json();

  if (json.length > 0) {
    dendros.innerHTML = '';
    json.forEach(dendro => {
      dendros.innerHTML += `
        <a href="/dendro.html?id=${dendro.id}" class="dendro">
          <img src="assets/img/icons/home.png" alt="${dendro.name}" />
          <p>${dendro.name}</p>
        </a>
      `;
    });


  } else {
    console.log('Nenhuma estufa encontrada!');
  }
};

//Função para ler os Dendros individualmente
async function getDendro(id) {
  console.log(id);
  const [resposeDendro] = await Promise.all([
    fetch(URL + `/${id}`)
  ]);

  const dataDendro = await resposeDendro.json();
  console.log(dataDendro);

  const title = document.querySelector('.dendroTitle');
  const temp = document.querySelector('.temperature');
  const hum = document.querySelector('.humidity');
  const light = document.querySelector('.light');

  title.innerHTML = dataDendro.name;
  temp.innerHTML = dataDendro.temperature;
  hum.innerHTML = dataDendro.humidity;
  light.innerHTML = dataDendro.light;
  
}

  if (!dendroId) {
    readDendros();
  } else {
    console.log(dendroId);
    getDendro(dendroId);
  }




