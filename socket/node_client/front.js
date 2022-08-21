const input = document.querySelector("#user-input");
const button = document.querySelector("#user-button");
const content = document.querySelector("#chat-content");


button.addEventListener("click", async () => {
    console.log(input.value);
    const data  = await fetch("/send", {
        method: "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify({
            data: input.value.toString()
        })
    });
    input.value("");
})