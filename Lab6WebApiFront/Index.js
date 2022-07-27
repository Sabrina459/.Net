window.addEventListener("DOMContentLoaded", () => {
    $.get("https://localhost:5001/api/Home").done((data) => {
        console.log(data)
        let content = ""
        var form = new FormData()
            data.forEach((good) => {
                const link = `http://localhost:63343/Lab6WebApiFront/MakeOrder.html?id=${good.id}`;
                content += '<tr>' +
                '<td id="id">'+good.id+'</td>' +
                '<td>'+good.name+'</td>' +
                '<td>'+good['price']+'</td>' +
                '<td>'+good['quantity']+'</td>'+
                '<td>'+'<a href="' + link + '" >'+'Make Order'
                +'</td>' +'</tr>'
                form.append('id',good.id)

            })
        document.querySelector("#list").innerHTML += content
    })



})