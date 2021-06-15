from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
import json
# import random

def main(request):
  return render(request, 'project/main.html', {})

def detail(request, pk):
  context = {'pk': pk}
  return render(request, 'project/detail.html', context)


def get_distance(request):
  if request.method == 'GET':
    return HttpResponse("The url was wrong......so there's nothing we can do:(")
  else:
    # distance = random.randint(1, 100)
    data = json.loads(request.body)
    distance = data.get('value', None)

    return JsonResponse({
      "distance": distance
    })