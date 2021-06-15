from django.shortcuts import render
from django.http import HttpResponse, JsonResponse
import json
# import random

global_distance = 0

def main(request):
  return render(request, 'project/main.html', {})

def detail(request, pk):
  context = {
    'pk': pk,
    'distance': global_distance
  }
  return render(request, 'project/detail.html', context)


def get_distance(request):
  global global_distance
  if request.method == 'GET':
    return JsonResponse({
      "distance": global_distance
    })
  else:
    # distance = random.randint(1, 100)
    data = json.loads(request.body)
    distance = data.get('value', None)
    global_distance = distance

    return JsonResponse({
      "distance": global_distance
    })