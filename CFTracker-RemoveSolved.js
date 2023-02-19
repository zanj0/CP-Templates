function removeElementsByClass(className){
    const elements = document.getElementsByClassName(className);
    while(elements.length > 0){
        elements[0].parentNode.removeChild(elements[0]);
    }
}
removeElementsByClass("bg-success-light w-50  p-2");
removeElementsByClass("bg-success-light w-100  p-2");
