// http://localhost:8080/api/v1/dendro
URL = 'https://sv95h56n-8080.brs.devtunnels.ms/api/v1/dendro';

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
  const [resposeDendro] = await Promise.all([
    fetch(URL + `/${id}`)
  ]);

  const dataDendro = await resposeDendro.json();
  console.log(dataDendro);

  const title = document.querySelector('.dendroTitle');
  const sliderValue = document.querySelector('.sliderVal');
  const slider = document.querySelector('.slider');

  title.innerHTML = dataDendro.name;
  slider.value = dataDendro.position;
  sliderValue.innerHTML = slider.value;
  
}

if (!dendroId) {
  readDendros();
} else {
  console.log(dendroId);
  getDendro(dendroId);
}

var slider = document.getElementById("myRange");
var output = document.getElementById("sliderVal");
output.innerHTML = slider.value; // Display the default slider value

// Update the current slider value (each time you drag the slider handle)
slider.oninput = function() {
  output.innerHTML = this.value;
  updateDendro(dendroId, this.value);
}

// Função para atualizar a posição do dendro
const updateDendro = async (id, position) => {
  let response = await fetch(URL + `/${id}`, {
    method: 'PATCH',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({
      position: position
    })
  });

  let json = await response.json();
  console.log(json);
};

